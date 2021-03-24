#include "impl.h"
#include <vector>
#include <stack>
#include <algorithm>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isCloseBracket(const char bracket) {
    auto resultIter = std::find_if(brackets.begin(), brackets.end(), [bracket](const std::pair<char, char> value) {
        return value.second == bracket;
    });
    return resultIter != brackets.end();
}

bool isValid(const std::string& source) {
    std::stack<char> bracketsStack;

    for (const char &symbol : source) {
        auto resultIter = std::find_if(brackets.begin(), brackets.end(), [symbol](const std::pair<char, char> value) {
            return value.first == symbol;
        });

        if (resultIter != brackets.end()) {
            bracketsStack.push(resultIter->second);
        } else if (isCloseBracket(symbol)) {
            if (bracketsStack.empty() || bracketsStack.top() != symbol) {
                return false;
            }
            if (bracketsStack.top() == symbol) {
                bracketsStack.pop();
            }
        }
    }

    return bracketsStack.empty();
}
