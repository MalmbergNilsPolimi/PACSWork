/**
 * @file main.cpp
 * @brief Main program.
 */


#include <iostream>
#include <cmath>
#include "main.hpp"
#include "json_parser.hpp"
#include "search_min.hpp"
#include "vect_operations.hpp"


int main() {

    Parameters readParams;
    readParametersFromJson(readParams, "parameters.json");
    printParametersFromJson(readParams);

    auto functionToMinimize = [](const std::vector<double>& x) -> double {
        // The user define here the multivariate function
        return x[0] * x[1] + 4 * std::pow(x[0],4) + x[1] * x[1] + 3 * x[0];
    };

    auto functionGradient = [](FunctionWrapper function, const std::vector<double>& x, unsigned int& methodGradient) -> std::vector<double> {
        
        std::vector<double> grad(x.size());

        switch (methodGradient)
        {
        
        case 0:
            // The user can define here the gradient
            grad[0] = x[1] + 16 * std::pow(x[0],3) + 3;
            grad[1] = x[0] + 2 * x[1];
             break;
        
        default:
            static bool errorDisplayed{false};
            if (methodGradient != 1) {
                if (!errorDisplayed) {
                    std::cerr << "Wrong definition of the gradient method in JSON file. Use of method 1." << std::endl;
                    errorDisplayed = true;
                }
            }
            
            // Use of finite difference method 
            double step{1e-6};           
            grad = FDgradient(function, x,  step);
            break;
        }
        
        return grad;
    };

    std::vector<double> minPoint = searchMinimum(functionToMinimize, functionGradient, readParams);
    
    std::cout << "Minimum coordinates : [ ";
    for (size_t i = 0; i < readParams.numVar; ++i) {
        std::cout << minPoint[i] << " ";
    }
    std::cout << "]" << std::endl;

    std::cout << "Value of the minimum : " << functionToMinimize(minPoint) << std::endl;
    
    return 0;
}