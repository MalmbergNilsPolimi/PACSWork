/**
 * @file search_min.hpp
 * @brief Definition of the functions used to compute the minimum.
 */


#ifndef SEARCH_MIN_HPP
#define SEARCH_MIN_HPP

#include <functional> // for std::function
#include "main.hpp"


using FunctionWrapper = const std::function<double(const std::vector<double>&)>&;
using FunctionWrapperGradient = const std::function<std::vector<double>(FunctionWrapper, const std::vector<double>&, int&)>&;


/**
 * @brief Compute the learning rate at a step k using several methods.
 * 
 * @param functionToMinimize Multivariate function to minimise.
 * @param functionGradient Gradient of the multivariate function.
 * @param readParams Parameters extracted from the JSON file.
 * @param vectXk Vector containing the minimum point at step k.
 * @param k Number of iteration.
 */
double learningRate(FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient, Parameters readParams, std::vector<double> vectXk, int& k);

/**
 * @brief Compute the minimum of a multivariate function.
 * 
 * @param functionToMinimize Multivariate function to minimise.
 * @param functionGradient Gradient of the multivariate function.
 * @param readParams Parameters extracted from the JSON file.
 */
std::vector<double> searchMinimum(FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient, Parameters& readParams);


#endif // SEARCH_MIN_HPP