#include "exportVTK.hpp"

#include <iostream>
#include <mpi.h>
#include <fstream>
#include <vector>

// Function to write the solution to a VTK file
void write_vtk(const std::vector<std::vector<double>>& U, int n, double h, int rank, int dim) {
    int local_n = U.size();
    
    std::vector<double> local_data(n * local_n);
    for (int i = 0; i < local_n; ++i) {
        std::copy(U[i].begin(), U[i].end(), local_data.begin() + i * n);
    }
    
    std::vector<double> all_solutions;
    if (rank == 0) {
        all_solutions.resize(n * n);
    }
    
    MPI_Gather(local_data.data(), n * local_n, MPI_DOUBLE, all_solutions.data(), n * local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);  

    if (rank == 0) {
        std::ofstream file("solution.vtk");
        file << "# vtk DataFile Version 2.0\n";
        file << "Laplace Solution\n";
        file << "ASCII\n";
        file << "DATASET STRUCTURED_GRID\n";
        file << "DIMENSIONS " << n << " " << n << " 1\n";
        file << "POINTS " << n * n << " float\n";
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                if (dim==3)
                {
                    file << i * h << " " << j * h << " " << all_solutions[j * n + i] << "\n";
                } else {
                    file << i * h << " " << j * h << " 0.0\n";
                }   
            }
        }

        if (dim != 3)
        {
            file << "POINT_DATA " << n * n << "\n";
            file << "SCALARS solution float 1\n";
            file << "LOOKUP_TABLE default\n";
            for (int j = 0; j < n; ++j) {
                for (int i = 0; i < n; ++i) {
                    file << all_solutions[j * n + i] << "\n";
                }
            }
        } 
        file.close();
    }
}