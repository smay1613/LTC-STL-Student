#include "impl.h"
#include <vector>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isBracket(char c, char& matchOpenBracket, bool& isOpening, bool& isClosing)
{
    for (auto& bracket : brackets)
    {
        if (bracket.first != c && bracket.second != c)
            continue;

        matchOpenBracket = bracket.first;
        isOpening = bracket.first == c;
        isClosing = bracket.second == c;

        return isOpening || isClosing;
    }

    return false;
}

bool isValid(const std::string& source)
{
    std::stack<char> stack;

    bool isOpeningBracket = false;
    bool isClosingBracket = false;
    char matchOpenBracket = '\0';

    for (auto& c : source)
    {
        if (!isBracket(c, matchOpenBracket, isOpeningBracket, isClosingBracket))
            continue;

        if (isOpeningBracket)
        {
            stack.push(c);
        }
        else if (isClosingBracket)
        {
            if (stack.empty())
                return false;

            bool isLastBracketMatching = matchOpenBracket == stack.top();

            if (!isLastBracketMatching)
                return false;

            stack.pop();
        }
    }

    return stack.empty();
}
