#pragma once
#include <string>
#include <stack>

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
bool isValid(const std::string& source) {
    std::stack<char> stack;
    for (auto const &c : source) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (stack.empty()) {
                return false;
            }
            char ch = stack.top();
            stack.pop();
            switch (ch) {
                case '(':
                    if (c != ')') {
                        return false;
                    }
                    break;
                case '[':
                    if (c != ']') {
                        return false;
                    }
                    break;
                case '{':
                    if (c != '}') {
                        return false;
                    }
                    break;
            }
        }
    }
    if (!stack.empty()) {
        return false;
    }
    return true;
}
