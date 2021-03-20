#include "impl.h"
#include <vector>
#include <algorithm>
#include <stack>

namespace {
    const std::vector<std::pair<char, char>> brackets {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'}
    };
}

bool isValid(const std::string& source) {
    std::stack<char> bracketsStack;

    for(char symbol : source) {
        auto itOpen = std::find_if(std::begin(brackets), std::end(brackets), [symbol](const std::pair<char, char> value) {
                                                                             return symbol == value.first;
                                                                         });
        if(itOpen != std::end(brackets)) {
            bracketsStack.push(symbol);
            continue;
        }

        auto itClose = std::find_if(std::begin(brackets), std::end(brackets), [symbol](const std::pair<char, char> value) {
                                                                             return symbol == value.second;
                                                                         });

        if(itClose != std::end(brackets)) {
            if( bracketsStack.empty() || (*itClose).first != bracketsStack.top()) {
                return false;
            }
            bracketsStack.pop();
            continue;
        }
    }

    if(bracketsStack.empty()) {
        return true;
    }

    return false;
}
