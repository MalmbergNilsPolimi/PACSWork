#ifndef SEARCH_MIN_HPP
#define SEARCH_MIN_HPP

#include <functional> // for std::function
#include "main.hpp"

using FunctionWrapper = const std::function<double(const std::vector<double>&)>&;
using FunctionWrapperGradient = const std::function<std::vector<double>(const std::vector<double>&)>&;

double vectorNorm(const std::vector<double>& vect);
std::vector<double> vectorDiff(const std::vector<double>& vect1, const std::vector<double>& vect2);
std::vector<double> prodVectWithCst(const std::vector<double>& vect, const double& constant);
double learningRate(double& alpha0, double& mu, int methodLearningRate, int& k, FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient, std::vector<double> vectXk);
std::vector<double> searchMinimum(FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient, Parameters& readParams);

#endif // SEARCH_MIN_HPP