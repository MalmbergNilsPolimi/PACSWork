/**
 * @file json_parser.hpp
 * @brief Definition of the function used to extract and print data from a JSON file.
 */


#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include "main.hpp" // include struct definition


/**
 * @brief Extract paramaters from a JSON file.
 * 
 * @param params Struct that will containt the extracted parameters.
 * @param filename Name of the JSON file.
 */
void readParametersFromJson(Parameters& params, const std::string& filename);

/**
 * @brief Print in the terminal the parameters contained in the struct.
 * 
 * @param readParams Struct containing the parameters.
 */
void printParametersFromJson(Parameters readParams);


#endif // JSON_PARSER_HPP