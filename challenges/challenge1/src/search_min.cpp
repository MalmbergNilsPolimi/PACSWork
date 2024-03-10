#include <iostream>
#include <cmath>
#include <algorithm>
#include "search_min.hpp"

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

double learningRate(double& alpha0, double& mu, int methodLearningRate, int& k, FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient) {
    double rate;

    switch(methodLearningRate) {
        case 0:
            // Exponential decay
            rate = alpha0 * std::exp(- mu * k);
            break;
        case 1:
            // Inverse decay
            rate = alpha0 / (1 + mu * k);
            break;
        case 2:
            // Approximate line search with Armijo rule
            rate = 2;
            break;
        default:
            // Wrong value
            std::cerr << "Wrong definition of the Learning rate in JSON file. Use of method 0." << std::endl;
            methodLearningRate = 0;
            rate = learningRate(alpha0, mu, methodLearningRate, k, functionToMinimize, functionGradient);
    }
    return rate;
}

std::vector<double> searchMinimum(FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient, Parameters& readParams) {
    std::cout << "Searching for the minimum..." << std::endl;

    std::vector<double> vectX1((readParams.initialConditions).size());
    
    std::copy(std::begin(readParams.initialConditions), std::end(readParams.initialConditions), std::begin(vectX1));

    int iter=0;
    double alphak = learningRate(readParams.alpha0, readParams.mu, readParams.methodLearningRate, iter, functionToMinimize, functionGradient);
    std::vector<double> vectX2 = vectorDiff(vectX1, prodVectWithCst(functionGradient(vectX1), alphak));
    ++iter;

    while (iter <= readParams.maxIter && vectorNorm(vectorDiff(vectX2, vectX1)) >= readParams.lTol && vectorNorm(functionGradient(vectX1)) >= readParams.rTol) {
        std::copy(std::begin(vectX2), std::end(vectX2), std::begin(vectX1));
        alphak = learningRate(readParams.alpha0, readParams.mu, readParams.methodLearningRate, iter, functionToMinimize, functionGradient);
        std::vector<double> tmpVect = vectorDiff(vectX1, prodVectWithCst(functionGradient(vectX1), alphak));
        std::copy(std::begin(tmpVect), std::end(tmpVect), std::begin(vectX2));
        ++iter;
    }

    return vectX2;
}