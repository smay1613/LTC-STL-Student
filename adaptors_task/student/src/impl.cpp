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
    std::stack<char> openBrackets;

    for (char ch : source)
    {
        auto pairIt = std::find_if(brackets.cbegin(), brackets.cend(),
                                   [ch] (const std::pair<char, char>& p)
                                        {
                                            return p.first == ch || p.second == ch;
                                        });

        if (pairIt != brackets.cend())
        {
            if (pairIt->first == ch)
            {
                openBrackets.push(ch);
            }
            else
            {
                if (openBrackets.empty() || pairIt->first != openBrackets.top())
                {
                    return false;
                }
                openBrackets.pop();
            }
        }
    }

    return openBrackets.empty();
}
