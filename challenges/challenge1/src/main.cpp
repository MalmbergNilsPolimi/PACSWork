#include <iostream>
#include <cmath>
#include "main.hpp"
#include "json_parser.hpp"
#include "search_min.hpp"

int main() {

    Parameters readParams;
    readParametersFromJson(readParams, "parameters.json");
    printParametersFromJson(readParams);

    auto functionToMinimize = [](const std::vector<double>& x) { // & is used to give a reference, to avoid function to copy x
        return x[0] * x[1] + 4 * std::pow(x[0],4) + x[1] * x[1] + 3 * x[0];
    };

     auto functionGradientUserDefine = [](const std::vector<double>& x) -> std::vector<double> {
        std::vector<double> grad(2);
        grad[0] = x[1] + 16 * std::pow(x[0],3) + 3;
        grad[1] = x[0] + 2 * x[1];
        return grad;
    };

    std::vector<double> minPoint = searchMinimum(functionToMinimize, functionGradientUserDefine, readParams);

    std::cout << "Minimum coordinates : [ ";
    for (size_t i = 0; i < minPoint.size(); ++i) {
        std::cout << minPoint[i] << " ";
    }
    std::cout << "]" << std::endl;

    std::cout << "Value of the minimum : " << functionToMinimize(minPoint) << std::endl;

    return 0;
}