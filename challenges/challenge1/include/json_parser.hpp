#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include "main.hpp" // include struct definition

void readParametersFromJson(Parameters& params, const std::string& filename);
void printParametersFromJson(Parameters readParams);

#endif // JSON_PARSER_HPP