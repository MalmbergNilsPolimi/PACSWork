#include <iostream>
#include <fstream>
#include "json_parser.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void readParametersFromJson(Parameters& params, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        json j;
        file >> j;
        params.alpha0 = j["alpha0"].get<double>();
        params.mu = j["mu"].get<double>();
        params.maxIter = j["maxIter"].get<int>();
        params.lTol = j["lTol"].get<double>();
        params.rTol = j["rTol"].get<double>();
        params.initialConditions = j["initialConditions"].get<std::vector<double>>();
        params.methodLearningRate = j["methodLearningRate"].get<int>();
        file.close();
    } else {
        std::cerr << "Error opening file " << filename << std::endl;
    }
}

void printParametersFromJson(Parameters readParams) {
    std::cout << "Parameters read from JSON file:\n";
    std::cout << "alpha0: " << readParams.alpha0 << std::endl;
    std::cout << "mu: " << readParams.mu << std::endl;
    std::cout << "maxIter: " << readParams.maxIter << std::endl;
    std::cout << "lTol: " << readParams.lTol << std::endl;
    std::cout << "rTol: " << readParams.rTol << std::endl;
    std::cout << "Initial conditions: [ ";
    for (const auto& value : readParams.initialConditions) {
        std::cout << value << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "methodLearningRate: " << readParams.methodLearningRate << "\n" << std::endl;
}