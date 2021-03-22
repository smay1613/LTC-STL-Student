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

    for (const char &ch : source) {
        auto resultIter = std::find_if(brackets.begin(), brackets.end(), [ch](const std::pair<char, char> value) {
            return value.first == ch;
        });

        if (resultIter != brackets.end()) {
            bracketsStack.push((*resultIter).second);
        } else if (isCloseBracket(ch)) {
            if (bracketsStack.empty()) {
                return false;
            }
            if (bracketsStack.top() == ch) {
                bracketsStack.pop();
            }
        }
    }

    return bracketsStack.empty();
}
