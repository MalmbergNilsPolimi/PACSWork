#ifndef MAIN_HPP
#define MAIN_HPP

#include <vector>

struct Parameters
{
    double alpha0;
    double mu;
    int maxIter;
    double lTol;
    double rTol;
    std::vector<double> initialConditions;
    int methodLearningRate;
};

#endif // MAIN_HPP
