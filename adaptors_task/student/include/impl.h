#pragma once
#include <string>
#include <stack>
#include <algorithm>

bool isOpenBracket(const char ch);
bool isClosedBracket(const char ch);
bool isMirrored(const char ch1, const char ch2);
void validation(std::stack<char> & brackets, bool & isValid,const char ch);
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
