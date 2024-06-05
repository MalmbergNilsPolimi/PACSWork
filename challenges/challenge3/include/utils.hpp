#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

// Function declaration for setting boundary conditions
void make_boundaries(std::vector<std::vector<double>>& U, int rank, int size);

#endif // UTILS_HPP