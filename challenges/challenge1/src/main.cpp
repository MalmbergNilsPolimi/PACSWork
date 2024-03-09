#include <iostream>
#include <vector>

#include "json.hpp"
using json = nlohmann::json;

#include "json_parser.hpp"

struct Parameters
{
    double alpha0;
    double mu;
    int maxIter;
    double lTol; // tolerance for the control on the step length
    double rTol; // tolerance for the control on the residual 
    std::vector<double> initialConditions;

};

int main() {

    Parameters readParams;
    readParametersFromJson(readParams, "parameters.json");

    // Print all users parameters
    std::cout << "Parameters read from JSON file:\n";
    std::cout << "alpha0: " << readParams.alpha0 << std::endl;
    std::cout << "mu: " << readParams.mu << std::endl;
    std::cout << "maxIter: " << readParams.maxIter << std::endl;
    std::cout << "ltol: " << readParams.ltol << std::endl;
    std::cout << "rtol: " << readParams.rtol << std::endl;
    std::cout << "Initial conditions:\n";
    for (int i = 0; i < readParams.initialConditions.size(); ++i) {
        std::cout << "Initial condition " << i + 1 << ": " << readParams.initialConditions[i] << std::endl;
    }

    return 0;
}