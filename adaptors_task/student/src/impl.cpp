#include "impl.h"
#include <vector>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source) {
    std::stack<char> openedBrackets;
    for (auto const &c : source) {
        for (auto const &currentBracket : brackets) {
            if (const bool isOpenBracket = (c == currentBracket.first)) {
                openedBrackets.push(c);
                break;
            } else if (const bool isCloseBracket = (c == currentBracket.second)) {
                if (openedBrackets.empty()) {
                    return false;
                }
                char ch = openedBrackets.top();
                openedBrackets.pop();
                for (auto const &bracket : brackets) {
                    if (ch == bracket.first && c != bracket.second) {
                        return false;
                    }
                }
                break;
            }
        }
    }
    return openedBrackets.empty();
}
