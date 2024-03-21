/**
 * @file vect_operations.cpp
 * @brief Implementation of vector operations functions.
 */


#include <iostream>
#include <cmath>
#include "vect_operations.hpp"


double vectorNorm(const std::vector<double>& vect) {
    double sum_of_squares = 0.0;
    for (size_t i = 0; i < vect.size(); ++i) {
        sum_of_squares += vect[i] * vect[i];
    }
    return std::sqrt(sum_of_squares);
}


std::vector<double> vectorDiff(const std::vector<double>& vect1, const std::vector<double>& vect2) {
    std::vector<double> vectDiff(vect1.size());
    if (std::abs(static_cast<int>(vect1.size()) - static_cast<int>(vect2.size())) < 1e-6) {
        for (size_t i = 0; i < vect1.size(); ++i) {
            vectDiff[i] = vect1[i] - vect2[i];
        }
    } else {
        std::cerr << "Error operation on two vectors with different dimensions" << std::endl;
    }
    return vectDiff;
}


std::vector<double> prodVectWithCst(const std::vector<double>& vect, const double& constant) {
    std::vector<double> newVect(vect.size());
        for (size_t i = 0; i < vect.size(); ++i) {
            newVect[i] = constant * vect[i];
        }
    return newVect;
}


std::vector<double> vectorSum(const std::vector<double>& vect1, const std::vector<double>& vect2) {
    std::vector<double> newVect(vect1.size());

    if (std::abs(static_cast<int>(vect1.size()) - static_cast<int>(vect2.size())) < 1e-6) {
        for (size_t i = 0; i < vect1.size(); ++i) {
            newVect[i] = vect1[i] + vect2[i];
        }
    } else {
        std::cerr << "Error operation on two vectors with different dimensions" << std::endl;
    }

    return newVect;
}