#include <iostream>
#include <fstream>
#include "json_parser.hpp"
#include "json.hpp"
using json = nlohmann::json;

void readParametersFromJson(Parameters& params, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        json j;
        file >> j;
        params.alpha0 = j["alpha0"].get<double>();
        params.mu = j["mu"].get<double>();
        params.maxIter = j["maxIter"].get<int>();
        params.ltol = j["lTol"].get<double>();
        params.rtol = j["rTol"].get<double>();
        params.initialConditions = j["initialConditions"].get<std::vector<double>>();
        file.close();
    } else {
        std::cerr << "Error opening file " << filename << std::endl;
    }
}