#include <iostream>
#include "main.hpp"
#include "json_parser.hpp"

int main() {

    Parameters readParams;
    readParametersFromJson(readParams, "parameters.json");

    // Print all users parameters
    std::cout << "Parameters read from JSON file:\n";
    std::cout << "alpha0: " << readParams.alpha0 << std::endl;
    std::cout << "mu: " << readParams.mu << std::endl;
    std::cout << "maxIter: " << readParams.maxIter << std::endl;
    std::cout << "ltol: " << readParams.lTol << std::endl;
    std::cout << "rtol: " << readParams.rTol << std::endl;
    std::cout << "Initial conditions: ";
    for (const auto& value : readParams.initialConditions) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}