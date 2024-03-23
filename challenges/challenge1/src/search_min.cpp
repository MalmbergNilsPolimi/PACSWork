/**
 * @file search_min.cpp
 * @brief Implementation of vector operations and minimization functions.
 */


#include <iostream>
#include <cmath>
#include "search_min.hpp"
#include "vect_operations.hpp"


double learningRate(FunctionWrapper functionToMinimize, FunctionWrapperGradient functionGradient, Parameters readParams,
                    std::vector<double> vectXk, unsigned int& k) {
    
    static bool errorDisplayed{false};
    static bool errorDisplayed2{false};

    unsigned int methodLearningRate{readParams.methodLearningRate};
    unsigned int methodGradient{readParams.methodGradient};

    double rate;
    double sigma{0.5};
    double alpha0{readParams.alpha0};
    double mu{readParams.mu};
    
    std::vector<double> gradient(readParams.numVar);

    if ((readParams.methodMinimization==1 || readParams.methodMinimization==2) && readParams.methodLearningRate==2) {
        if (!errorDisplayed2) {
            std::cerr << "You can't use the Armijo rule with the heavy-ball or Nesterov method. Use of exponential decay." << std::endl;
            readParams.methodLearningRate=0;
            errorDisplayed2=true;
        }
    }
    
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
            gradient = functionGradient(functionToMinimize ,vectXk, methodGradient);
            while (functionToMinimize(vectXk) - functionToMinimize(vectorDiff(vectXk, prodVectWithCst(gradient, alpha0))) < sigma*alpha0*vectorNorm(gradient)*vectorNorm(gradient)) {
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
    std::cout << "Searching for the minimum..." << std::endl;

    unsigned int iter{0};

    std::vector<double> vectX1(readParams.numVar);
    std::vector<double> vectX2(readParams.numVar);   
    std::vector<double> vectX3(readParams.numVar);    
    std::copy(std::begin(readParams.initialConditions), std::end(readParams.initialConditions), std::begin(vectX1));

    double alphak = learningRate(functionToMinimize, functionGradient, readParams, vectX1, iter);
    
    std::vector<double> vectd1(readParams.numVar);
    std::vector<double> vectd2(readParams.numVar);
    std::vector<double> vectY(readParams.numVar);
    std::copy(std::begin(readParams.initialConditions), std::end(readParams.initialConditions), std::begin(vectY));

    double eta{0.9};

    auto etaCalc = [](double& alpha) -> double {
        double eta{0.9};
        if (alpha < 1)
        {
            eta = 1-alpha;
        }
        
        return eta;
    };

    bool flag{true};

    switch (readParams.methodMinimization)
    {
    case 0:
        //Gradient method
        vectX2 = vectorDiff(vectX1, prodVectWithCst(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient), alphak));
        ++iter;
        while (iter <= readParams.maxIter 
                    && vectorNorm(vectorDiff(vectX2, vectX1)) >= readParams.lTol 
                    && vectorNorm(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient)) >= readParams.rTol)
        {
            std::copy(std::begin(vectX2), std::end(vectX2), std::begin(vectX1));
            alphak = learningRate(functionToMinimize, functionGradient, readParams, vectX1, iter);
            std::vector<double> tmpVect = vectorDiff(vectX1, prodVectWithCst(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient), alphak));
            std::copy(std::begin(tmpVect), std::end(tmpVect), std::begin(vectX2));
            ++iter;
        }
        break;

    case 1:
        //Heavy-ball, momentum method -> not working
        vectd1 = prodVectWithCst(functionGradient(functionToMinimize, vectX1, readParams.methodGradient), -alphak);
        vectX2 = vectorSum(vectX1, vectd1);
        ++iter;
        while (iter <= readParams.maxIter
                    && vectorNorm(vectorDiff(vectX2, vectX1)) >= readParams.lTol
                    && vectorNorm(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient)) >= readParams.rTol)
        {
            alphak = learningRate(functionToMinimize, functionGradient, readParams, vectX2, iter);

            eta = etaCalc(alphak);

            vectd2 = vectorSum(prodVectWithCst(vectd1, eta), prodVectWithCst(functionGradient(functionToMinimize ,vectX2, readParams.methodGradient) , -alphak));

            vectX1 = vectorSum(vectX2, vectd2);

            std::copy(std::begin(vectd2), std::end(vectd2), std::begin(vectd1));
            std::copy(std::begin(vectX1), std::end(vectX1), std::begin(vectX2));
            ++iter;
        }
        std::cout << "Number iter: " << iter << std::endl;
        break;

    case 2:
        //Nesterov -> not working
        iter=1;
        alphak = learningRate(functionToMinimize, functionGradient, readParams, vectX1, iter);
        vectX2 = prodVectWithCst(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient),-alphak);

        while (iter <= readParams.maxIter
                    && vectorNorm(vectorDiff(vectX2, vectX1)) >= readParams.lTol
                    && vectorNorm(functionGradient(functionToMinimize ,vectX1, readParams.methodGradient)) >= readParams.rTol)
        {
            eta = etaCalc(alphak);
            vectY = vectorSum(vectX2, prodVectWithCst(vectorSum(vectX2,prodVectWithCst(vectX1, -1.)), eta));
            vectX3 = vectorSum(vectY, prodVectWithCst(functionGradient(functionToMinimize ,vectY, readParams.methodGradient), -alphak));
            
            std::copy(std::begin(vectX2), std::end(vectX2), std::begin(vectX1));
            std::copy(std::begin(vectX3), std::end(vectX3), std::begin(vectX2));
            ++iter;
            alphak = learningRate(functionToMinimize, functionGradient, readParams, vectX2, iter);
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