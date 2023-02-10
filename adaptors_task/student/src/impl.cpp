#include "impl.h"
#include <vector>
#include <stack>
#include <algorithm>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source)
{
    std::stack<char> stack;

    for (auto& c : source)
    {
        auto it = std::find_if(brackets.begin(), brackets.end(), [&](const std::pair<char, char>& p) -> bool {
            return p.first == c || p.second == c;
        });

        if (it == brackets.end())
            continue; // Not a bracket

        if (stack.empty())
        {
            stack.push(c);
            continue;
        }

        if (it->first == c)
        {
            // Opening bracket
            stack.push(c);
        }
        else if (it->second == c)
        {
            // Closing bracket
            char lastChar = stack.top();

            // Check if last opening bracket matches closing bracket
            if (lastChar == it->first)
            {
                stack.pop();
            }
        }
    }

    return stack.empty();
}
