#include "impl.h"
#include <map>
#include <stack>
#include <algorithm>

const std::map<char, char> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string &source)
{
    std::stack<char> checkBrackets;

    auto isWrongPair = [](const std::map<char, char>& brackets, const char& symbol)
    {
        return std::any_of(brackets.begin(), brackets.end(),
                                         [&symbol](const std::pair<const char, char>& pair) { return symbol == pair.second ? true : false; });
    };

    for(const auto& symbol : source)
    {
        if(brackets.find(symbol) != brackets.end())
            checkBrackets.emplace(symbol);
        else
        {
            if(!checkBrackets.empty() && symbol == brackets.at(checkBrackets.top()))
                checkBrackets.pop();
            else if ( isWrongPair(brackets, symbol) )
                return false;

        }
    }

    return checkBrackets.empty();
}
