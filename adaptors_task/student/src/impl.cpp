#include "impl.h"
#include <vector>

#include <algorithm>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source)
{
    bool ret = true;
    std::stack<char> tempBrackets;
    for (const char c : source)
    {
        auto currentBracket = std::find_if(brackets.cbegin(), brackets.cend(),
            [c](const std::pair<char, char>& type) { return c == type.first || c == type.second; } );

        if (currentBracket != brackets.cend())
        {
            if (c == currentBracket->first)
            {
                tempBrackets.push(c);
            }
            else if (!tempBrackets.empty() && tempBrackets.top() == currentBracket->first)
            {
                tempBrackets.pop();
            }
            else
            {
                ret = false;
                break;
            }
        }
    }
    return ret && tempBrackets.empty();
}
