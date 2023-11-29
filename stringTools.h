#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H
#include <Arduino.h>
#include <vector>


/**
 * Splits a string into a vector of strings, each string being an argument.
 * @warning Will remove the command name from the string!
 * @param string The string to split.
 * @param argv The vector to put the arguments in.
 * may return an empty vector if there are no arguments.
*/
void splitString(String string, std::vector<String>* argv);


/**
 * Splits a string into a vector of strings, each string being an argument.
 * @warning Will remove the command name from the string!
 * @param string The string to split.
 * @return A vector of strings, each string being an argument.
 * may return an empty vector if there are no arguments.
*/
std::vector<String> splitStringtoVec(String string);

/**
 * Joins a vector of strings into one string.
 * @param argv The vector of strings to join.
 * @param separator The string to put between each string.
 * @return The joined string.
*/
String joinString(std::vector<String>* argv, String separator = " ");

#endif