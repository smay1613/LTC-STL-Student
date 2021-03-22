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
    std::stack<char> bracketStack;

    for (auto ch : source)
    {
        for (auto br : brackets)
        {
            if (ch == br.first)
            {
                bracketStack.emplace(ch);
                break;
            }
            else if (ch == br.second)
            {
                if (bracketStack.empty() ||
                    std::end(brackets) == std::find(std::begin(brackets), std::end(brackets), std::make_pair(bracketStack.top(), ch)))
                {
                    return false;
                }

                bracketStack.pop();
                break;
            }
        }
    }

    return bracketStack.empty();
}
