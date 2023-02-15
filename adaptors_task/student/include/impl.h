#pragma once
#include <string>

/**
 * @todo isValid - check if given expression is valid - all open brackets are closed
 * by CORRESPONDING closed bracket.
 *
 * @param source - expression that will contain brackets
 * of three types: "()"/"[]"/"{}".
 * May contain other symbols or may not contain anything.
 *
 * @return true if expression is valid
 */
bool isValid(const std::string& source);
