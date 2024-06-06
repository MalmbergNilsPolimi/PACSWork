#ifndef EXPORT_VTK_HPP
#define EXPORT_VTK_HPP

#include <vector>

// Function to write the solution to a VTK file
void write_vtk(const std::vector<std::vector<double>>& U, int n, double h, int rank);

#endif // EXPORT_VTK_HPP