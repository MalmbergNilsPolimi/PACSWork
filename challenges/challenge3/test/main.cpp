#include "utils.hpp"
#include "exportVTK.hpp"
#include "jacobi.hpp"

#include <cmath>

// Function to compute the source term f(x, y)
double f(double x, double y) {
    return 8 * M_PI * M_PI * sin(2 * M_PI * x) * sin(2 * M_PI * y);
}


int main(int argc, char *argv[]) {
    solve_jacobi(argc, argv, f);
    return 0;
}