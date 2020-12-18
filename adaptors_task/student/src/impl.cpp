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
    std::stack<char> parsedBrackets;
    for (const char c : source)
    {
        auto currentBracket = std::find_if(brackets.cbegin(), brackets.cend(),
            [c](const std::pair<char, char>& type) { return c == type.first || c == type.second; } );

        if (currentBracket != brackets.cend())
        {
            const bool isBracketOpen = c == currentBracket->first;
            const bool isCloseBracketEqualOpened = !parsedBrackets.empty() && parsedBrackets.top() == currentBracket->first;
            if (isBracketOpen)
            {
                parsedBrackets.push(c);
            }
            else if (isCloseBracketEqualOpened)
            {
                parsedBrackets.pop();
            }
            else
            {
                return false; //violation principe "one entry - one exit"
            }
        }
    }
    return parsedBrackets.empty();
}
