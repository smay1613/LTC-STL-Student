#include "impl.h"
#include <vector>
#include <algorithm>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

auto findBracket(const char bracket) -> std::vector<std::pair<char, char>>::const_iterator
{
    return std::find_if(brackets.cbegin(), brackets.cend(),
                        [bracket] (const std::pair<char, char>& p)
                        {
                            return p.first == bracket || p.second == bracket;
                        });
}

bool isValid(const std::string& source)
{
    std::stack<char> openBrackets;

    for (char sourceCharacter : source)
    {
        auto bracketsIt = findBracket(sourceCharacter);

        if (bracketsIt != brackets.cend())
        {
            bool isOpenBracket = bracketsIt->first == sourceCharacter;

            if (isOpenBracket)
            {
                openBrackets.push(sourceCharacter);
            }
            else
            {
                if (openBrackets.empty() || bracketsIt->first != openBrackets.top())
                {
                    return false;
                }
                openBrackets.pop();
            }
        }
    }

    return openBrackets.empty();
}
