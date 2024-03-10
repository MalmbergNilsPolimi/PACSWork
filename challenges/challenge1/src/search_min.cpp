#include <iostream>
#include "search_min.hpp"

std::vector<double> searchMinimum(FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient, Parameters& readParams) {
    std::cout << "Searching for the minimum..." << std::endl;
    std::vector<double> minPoint((readParams.initialConditions).size());

    for (size_t i = 0; i < minPoint.size(); ++i) {
        minPoint[i] = i;
    }

    return minPoint;
}
