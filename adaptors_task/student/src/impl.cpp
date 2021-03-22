#include "impl.h"
#include <map>
#include <algorithm>
#include <stack>

const std::map<char, char> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source)
{
    std::stack<char> checkStack;

    auto isCloseBracket = [](const char symbol) {
        auto result =std::find_if(brackets.begin(), brackets.end(), [symbol](std::pair<char, char>pair) {
                return pair.second == symbol;
    });
        return result != brackets.end();
    };

    for (auto bracket : source) {
        auto currentBracketPair = brackets.find(bracket);
        if (currentBracketPair != brackets.end()) {
            checkStack.emplace(bracket);
        } else {
            if (isCloseBracket(bracket)) {
                if (checkStack.empty()) {
                    return false;
                } else {
                    auto currentOpen = brackets.find(checkStack.top());
                    if (currentOpen->second == bracket) {
                        checkStack.pop();
                    } else {
                        return false;
                    }
                }
            }
        }
    }

    return checkStack.empty();
}
