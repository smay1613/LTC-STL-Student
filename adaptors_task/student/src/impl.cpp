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
    for (const char& c : source)
    {
        const auto it = std::find_if(brackets.cbegin(), brackets.cend(), [&](std::pair<char, char> const & pair)
        {
                return pair.first == c || pair.second == c;
        });
        if (it != brackets.end())
        {
            if (it->first == c)
            {
                stack.push(c);
            }
            else if (it->second == c)
            {
                if (stack.empty() || stack.top() != it->first)
                {
                    return false;
                }
                stack.pop();
            }
        }
    }
    return stack.empty();
}
