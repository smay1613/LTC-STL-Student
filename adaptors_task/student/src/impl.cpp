#include "impl.h"
#include <vector>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source) {
    std::stack<char> pairedBrackets;

    for (auto const& c : source) {
        for (auto const& bracket : brackets) {
            if ( c == bracket.first) {
                pairedBrackets.push(c);
                break;
            }
            else if ( c == bracket.second) {
                if (pairedBrackets.empty()) {
                    return false;
                }
                char lastBracket = pairedBrackets.top();
                pairedBrackets.pop();

                for (auto const& bracket_ : brackets) {
                    if (lastBracket == bracket_.first && c != bracket_.second) {
                        return false;
                    }
                }
                break;
            }
        }
    }
    return pairedBrackets.empty();
}