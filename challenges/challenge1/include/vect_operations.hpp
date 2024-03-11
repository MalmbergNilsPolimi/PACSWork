/**
 * @file vect_operations.hpp
 * @brief Definition of the functions used to do operations with vectors.
 */


#ifndef VECT_OP_HPP
#define VECT_OP_HPP

#include <vector>


/**
 * @brief Compute the norm of a vector.
 * 
 * @param vect Vector whose norm is to be calculated.
 */
double vectorNorm(const std::vector<double>& vect);

/**
 * @brief Compute the difference between two vectors.
 * 
 * @param vect1 Vector use for the calculations.
 * @param vect2 Vector use for the calculations.
 */
std::vector<double> vectorDiff(const std::vector<double>& vect1, const std::vector<double>& vect2);

/**
 * @brief Compute the term by term product of a vector and a constant.
 * 
 * @param vect Vector use for the calculations.
 * @param constant Constant use for the calculations.
 */
std::vector<double> prodVectWithCst(const std::vector<double>& vect, const double& constant);

#endif // VECT_OP_HPP