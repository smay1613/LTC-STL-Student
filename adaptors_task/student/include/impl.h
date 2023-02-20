#pragma once
#include <string>
#include <stack>
#include <unordered_map>

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
bool isValid(const std::string& source){
    std::unordered_map<char, char> brackets = {{')', '('}, {']', '['}, {'}', '{'}};
            std::stack<char> stack;
            for (char c : source) {
                if (brackets.count(c)) {
                    if (stack.empty() || stack.top() != brackets[c]) {
                        return false;
                    }
                    stack.pop();
                } else if (c == '(' || c == '[' || c == '{') {
                    stack.push(c);
                }
            }
            return stack.empty();
}
