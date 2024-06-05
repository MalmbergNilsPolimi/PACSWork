#ifndef JACOBI_HPP
#define JACOBI_HPP

#include <vector>

// Function declaration for solving using Jacobi iteration
void solve_jacobi(int argc, char *argv[], double (*f)(double, double));

#endif // JACOBI_HPP