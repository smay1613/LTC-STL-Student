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
            return (p.first == bracket || p.second == bracket) ? true : false;
        });
        if (it == brackets.end()) {
            continue;
        }
        if (it->first == bracket) {
            stack.push(bracket);
        } else {
            if (stack.empty()) {
                return false;
            }
            if (stack.top() != it->first) {
                return false;
            }
            stack.pop();
        }
    }
    return stack.empty();
}
