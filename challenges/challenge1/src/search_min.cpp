/**
 * @file search_min.cpp
 * @brief Implementation of vector operations and minimization functions.
 */


#include <iostream>
#include <cmath>
#include "search_min.hpp"
#include "vect_operations.hpp"


double learningRate(FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient, Parameters readParams, std::vector<double> vectXk, int& k) {
    double rate;
    double alpha0{readParams.alpha0};
    double mu{readParams.mu};
    int methodLearningRate{readParams.methodLearningRate};
    int methodGradient{readParams.methodGradient};
    double sigma{0.5};
    static bool errorDisplayed = false;

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
            if (readParams.methodMinimization==1) {
                std::cerr << "You can't use the Armijo rule with the heavy-ball method. Use of exponential decay." << std::endl;
                readParams.methodMinimization=0;
                learningRate(functionToMinimize, functionGradient, readParams, vectXk, k);
                break;
            }
            while (functionToMinimize(vectXk) - functionToMinimize(vectorDiff(vectXk, prodVectWithCst(functionGradient(functionToMinimize ,vectXk, methodGradient), alpha0))) < sigma*alpha0*vectorNorm(functionGradient(functionToMinimize ,vectXk, methodGradient))*vectorNorm(functionGradient(functionToMinimize ,vectXk, methodGradient))) {
                alpha0 /= 2;             
            }
            rate = alpha0;
            break;
        default:
            // Wrong value
            if (!errorDisplayed) {
                std::cerr << "Wrong definition of the learning rate in JSON file. Use of method 0." << std::endl;
                errorDisplayed = true;
            }
            readParams.methodLearningRate = 0;
            rate = learningRate(functionToMinimize, functionGradient, readParams, vectXk, k);
            break;
    }
    return rate;
}


std::vector<double> searchMinimum(FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient, Parameters& readParams) {
    static bool errorDisplayed = false;
    std::cout << "Searching for the minimum..." << std::endl;

    std::vector<double> vectX1((readParams.initialConditions).size());
    
    std::copy(std::begin(readParams.initialConditions), std::end(readParams.initialConditions), std::begin(vectX1));

    int iter=0;
    double alphak = learningRate(functionToMinimize, functionGradient, readParams, vectX1, iter);
    
    // Initialization for case 0
    std::vector<double> vectX2 = vectorDiff(vectX1, prodVectWithCst(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient), alphak));
    
    // Initialization for case 1
    std::vector<double> vectd2((readParams.initialConditions).size());

    double eta;
    if (alphak < 1) {
            eta = 1 - alphak;
    } else {
            eta = 0.9;
    }

    std::vector<double> vectd1 = prodVectWithCst(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient), -alphak);
    
    // Initialization for case 2
    std::vector<double> vectY = vectorSum(vectX1, prodVectWithCst(vectorSum(vectX1, prodVectWithCst(vectX1, -1.)) , eta));

    switch (readParams.methodMinimization)
    {
    case 0:
        //Gradient method
        ++iter;
        while (iter <= readParams.maxIter && vectorNorm(vectorDiff(vectX2, vectX1)) >= readParams.lTol && vectorNorm(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient)) >= readParams.rTol) {
            std::copy(std::begin(vectX2), std::end(vectX2), std::begin(vectX1));
            alphak = learningRate(functionToMinimize, functionGradient, readParams, vectX1, iter);
            std::vector<double> tmpVect = vectorDiff(vectX1, prodVectWithCst(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient), alphak));
            std::copy(std::begin(tmpVect), std::end(tmpVect), std::begin(vectX2));
            ++iter;
        }
        break;
    
    case 1:
        //Heavy-ball/momentum method
        vectX2 = vectorSum(vectX1, vectd1);

        while (iter <= readParams.maxIter && vectorNorm(vectorDiff(vectX2, vectX1)) >= readParams.lTol && vectorNorm(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient)) >= readParams.rTol)
        {
            vectX2 = vectorSum(vectX1, vectd1);

            ++iter;
            alphak = learningRate(functionToMinimize, functionGradient, readParams, vectX1, iter);
            
            if (alphak < 1) {
                eta = 1 - alphak;
            } else {
                eta = 0.9;
            }
            
            vectd2 = vectorSum(prodVectWithCst(vectd1, eta), prodVectWithCst(functionGradient(functionToMinimize ,vectX2, readParams.methodGradient) , -alphak));
            
            std::copy(std::begin(vectX2), std::end(vectX2), std::begin(vectX1));
            std::copy(std::begin(vectd2), std::end(vectd2), std::begin(vectd1));
        }
        
        break;

    case 2:
        //Nesterov method
        vectX2 = vectorSum(vectY, prodVectWithCst(functionGradient(functionToMinimize ,vectY, readParams.methodGradient), -alphak));        
        
        while (iter <= readParams.maxIter && vectorNorm(vectorDiff(vectX2, vectX1)) >= readParams.lTol && vectorNorm(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient)) >= readParams.rTol)
        {
            ++iter;
            alphak = learningRate(functionToMinimize, functionGradient, readParams, vectX2, iter);
            if (alphak < 1) {
                eta = 1 - alphak;
            } else {
                eta = 0.9;
            }
            std::copy(std::begin(vectX2), std::end(vectX2), std::begin(vectX1));
            vectX2 = vectorSum(vectX1, prodVectWithCst(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient), -alphak));
            vectY = vectorSum(vectX2, prodVectWithCst(vectorSum(vectX2, prodVectWithCst(vectX1, -1.)) , eta));
        }
        break;

    default:
        std::cerr << "Wrong definition of the minimization method. Use of method 0." << std::endl;
        readParams.methodMinimization = 0;
        vectX2 = searchMinimum(functionToMinimize, functionGradient, readParams);
        break;
    }

    return vectX2;
}