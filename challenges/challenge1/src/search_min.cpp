#include <iostream>
#include <cmath>
#include "search_min.hpp"

double learningRate(double& alpha0, double& mu, int& methodLearningRate, int& k) {
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
            std::cerr << "Wrong definition of the Learning rate in JSON file. Use of method 2." << std::endl;
            rate = learningRate(alpha0, mu, 2, k);
    }
    return rate;
}

std::vector<double> searchMinimum(FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient, Parameters& readParams) {
    std::cout << "Searching for the minimum..." << std::endl;
    std::vector<double> minPoint((readParams.initialConditions).size());

    for (size_t i = 0; i < minPoint.size(); ++i) {
        minPoint[i] = i;
    }

    int k = 1;
    double rate = learningRate(readParams.alpha0, readParams.mu, readParams.methodLearningRate, k);
    return minPoint;
}
