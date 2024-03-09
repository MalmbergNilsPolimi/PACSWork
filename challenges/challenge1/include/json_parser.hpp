#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include "main.hpp" // include struct definition

void readParametersFromJson(Parameters& params, const std::string& filename);

#endif // JSON_PARSER_HPP