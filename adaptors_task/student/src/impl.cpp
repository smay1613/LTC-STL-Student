#include "impl.h"
#include <vector>
#include <stack>
#include <algorithm>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string &source)
{
    std::stack<char> stack{};

    for (const auto c : source)
    {
        const auto typeIt = std::find_if(brackets.cbegin(), brackets.cend(),
                                         [c](const std::pair<char, char>& type)
                                         { return c == type.first || c == type.second; });
        const auto isMatchingClosingBracket = [c, typeIt, &stack]()
                                              { return !stack.empty() && stack.top() == typeIt->first && c == typeIt->second; };

        if (brackets.cend() == typeIt)
        {
            continue;
        }
        else if (isMatchingClosingBracket())
        {
            stack.pop();
        }
        else
        {
            stack.push(c);
        }
    }

    return stack.empty();
}
