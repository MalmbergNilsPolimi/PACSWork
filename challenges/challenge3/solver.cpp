#include <iostream>
#include <vector>
#include <cmath>
#include <mpi.h>
#include <omp.h>
#include <fstream>

// Function to compute the source term f(x, y)
double f(double x, double y) {
    return 8 * M_PI * M_PI * sin(2 * M_PI * x) * sin(2 * M_PI * y);
}

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

int main(int argc, char *argv[]) {
    // Initialize MPI
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initialize OpenMP
    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0) {
            std::cout << "Number of threads: " << omp_get_num_threads() << std::endl;
        }
    }

    // Define domain and parameters
    int n = (argc > 1) ? std::stoi(argv[1]) : 100;
    double tolerance = (argc > 2) ? std::stod(argv[2]) : 1e-6;
    int max_iter = (argc > 3) ? std::stoi(argv[3]) : 10000;
    double h = 1.0 / (n - 1);

    std::cout << "n: " << n << " tol: " << tolerance << " MaxIter: " << max_iter << std::endl;

    // Determine local domain size for each process
    int base_lines = n / size; // base number of lines per process
    int extra_lines = n % size; // number of processes that will get an extra line

    int local_n = base_lines + (rank < extra_lines ? 1 : 0); // distribute extra lines

    // Initialize matrices
    std::vector<std::vector<double>> U(local_n, std::vector<double>(n, 0.0)); // will contain the solution at iteration k
    std::vector<std::vector<double>> U_new(local_n, std::vector<double>(n, 0.0)); // will contain the solution at iteration k+1

    // Set boundary conditions
    for (int i = 0; i < local_n; ++i) {
        // Left and Right boundaries : first and last columns
        U[i][0] = U[i][n - 1] = 0.0;
    }
    if (rank == 0) {
        // Upper boundary : first row (only for the process 0 that will compute this part)
        for (int j = 0; j < n; ++j) {
            U[0][j] = 0.0;
        }
    }
    if (rank == size - 1) {
        // Lower boundary : last row (only for the process size-1 that will compute this part)
        for (int j = 0; j < n; ++j) {
            U[local_n - 1][j] = 0.0;
        }
    }

    // Jacobi Iteration
    double local_error;
    int iter = 0;
    bool converged = false;
    int global_converged;
    do {
        // Update internal points
        #pragma omp parallel for
        for (int i = 1; i < local_n - 1; ++i) {
            for (int j = 1; j < n - 1; ++j) {
                double x = j * h;
                double y = ((rank * base_lines) + std::min(rank, extra_lines) + i) * h;
                U_new[i][j] = 0.25 * (U[i - 1][j] + U[i + 1][j] + U[i][j - 1] + U[i][j + 1] + h * h * f(x, y));
            }
        }

        // Exchange boundary rows between adjacent processes to ensure the continuity of the solution
        if (rank > 0) {
            MPI_Sendrecv(&U_new[1][0], n, MPI_DOUBLE, rank - 1, 0, &U_new[0][0], n, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (rank < size - 1) {
            MPI_Sendrecv(&U_new[local_n - 2][0], n, MPI_DOUBLE, rank + 1, 0, &U_new[local_n - 1][0], n, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Compute local convergence criterion
        local_error = 0.0;
        #pragma omp parallel for reduction(+:local_error)
        for (int i = 1; i < local_n - 1; ++i) {
            for (int j = 1; j < n - 1; ++j) {
                local_error += (U_new[i][j] - U[i][j]) * (U_new[i][j] - U[i][j]);
            }
        }

        // Compute local error
        local_error = sqrt(local_error * h);

        // Check convergence on each process
        converged = (local_error < tolerance);

        // Communicate convergence status between all processes
        MPI_Allreduce(&converged, &global_converged, 1, MPI_INT, MPI_LAND, MPI_COMM_WORLD);

        // Update U matrix
        std::swap(U, U_new);

        iter++;
    } while (!global_converged && iter < max_iter);

    if (rank == 0) {
        if (global_converged) {
            std::cout << "Converged in " << iter << " iterations." << std::endl;
        } else {
            std::cout << "Did not converge within the maximum number of iterations." << std::endl;
        }
    }

    // Output solution
    write_vtk(U, n, h, size, rank);

    // Finalize MPI
    MPI_Finalize();
    return 0;
}