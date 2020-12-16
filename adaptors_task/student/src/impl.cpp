#include "impl.h"
#include <algorithm>
#include <stack>
#include <vector>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source)
{
    std::stack<char> stack;
    for (const auto& bracket : source) {
        auto it = std::find_if(brackets.begin(), brackets.end(), [&](std::pair<char, char> const p) {
            return p.first == bracket || p.second == bracket;
        });
        if (it != brackets.end()) {
            if (const bool isOpenBracket = it->first == bracket) {
                stack.push(bracket);
            }
            if (const bool isCloseBracket = it->second == bracket) {
                if (!stack.empty() && stack.top() == it->first) {
                    stack.pop();
                } else {
                    return false;
                }
            }
        }
    }
    return stack.empty();
}
