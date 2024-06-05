#include "exportVTK.hpp"

#include <iostream>
#include <mpi.h>
#include <fstream>

// Function to write the solution to a VTK file
void write_vtk(const std::vector<std::vector<double>>& U, int n, double h, int size, int rank) {
    std::vector<std::vector<double>> all_solutions(n, std::vector<double>(n * size)); // Stocke toutes les solutions
    MPI_Gather(&U[0][0], n * U.size(), MPI_DOUBLE, &all_solutions[0][0], n * U.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::ofstream file("solution.vtk");
        file << "# vtk DataFile Version 2.0\n";
        file << "Laplace Solution\n";
        file << "ASCII\n";
        file << "DATASET STRUCTURED_GRID\n";
        file << "DIMENSIONS " << n << " " << n * size << " 1\n";
        file << "POINTS " << n * n * size << " float\n";
        for (int k = 0; k < size; ++k) {
            for (int j = 0; j < n; ++j) {
                for (int i = 0; i < n; ++i) {
                    file << i * h << " " << j * h << " " << k * h << "\n";
                }
            }
        }
        file << "POINT_DATA " << n * n * size << "\n";
        file << "SCALARS solution float 1\n";
        file << "LOOKUP_TABLE default\n";
        for (int k = 0; k < size; ++k) {
            for (int j = 0; j < n; ++j) {
                for (int i = 0; i < n; ++i) {
                    file << all_solutions[i][j + k * n] << "\n";
                }
            }
        }
        file.close();
    }
}