#include "utils.hpp"

#include <mpi.h>

// Function to set boundary conditions
void make_boundaries(std::vector<std::vector<double>>& U, int rank, int size) {
    int n = U[0].size(); // Get the size of the local domain

    // Set boundary conditions based on process rank
    int local_n = U.size(); // Number of rows in the local domain
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
}