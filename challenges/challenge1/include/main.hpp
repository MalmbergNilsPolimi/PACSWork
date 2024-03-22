/**
 * @file main.hpp
 * @brief Definition of the struct Parameters.
 */


#ifndef MAIN_HPP
#define MAIN_HPP

#include <vector>

/**
 * @brief Struct containing the parameters.
 */
struct Parameters
{
    unsigned int numVar;
    double alpha0; /**< Initialisation of the learning rate. */
    double mu; /**< Decreasing coefficient. */
    unsigned int maxIter; /**< Maximum number of iteration. */
    double lTol; /**< Tolerance based on the control of the step length. */
    double rTol; /**< Tolerance based on the control of the residuals. */
    std::vector<double> initialConditions; /**< Starting point. */
    unsigned int methodLearningRate; /**< Method used for the learning rate computation. */
    unsigned int methodGradient; /**< Method used for the gradient computation. */
    unsigned int methodMinimization; /**< Method used to minimize the function. */
};


#endif // MAIN_HPP
