#ifndef SEARCH_MIN_HPP
#define SEARCH_MIN_HPP

#include <functional> // for std::function
#include "main.hpp"

using FunctionWrapper = const std::function<double(const std::vector<double>&)>&;
using FunctionWrapperGradient = const std::function<std::vector<double>(const std::vector<double>&)>&;

double learningRate(double& alpha0, double& mu, int& methodLearningRate, int& k);
std::vector<double> searchMinimum(FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient, Parameters& readParams);

#endif // SEARCH_MIN_HPP