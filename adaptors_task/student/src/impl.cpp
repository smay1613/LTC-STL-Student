#include "impl.h"
#include <vector>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source)
{
    std::stack<char> bracketsStack;
    std::string close;
    std::string open;

    for(auto bracket : brackets)
    {
        open+=bracket.first;
        close+=bracket.second;
    }

    for(auto character : source)
    {
        if(open.find(character) != std::string::npos)
        {
            bracketsStack.push(character);
        }
        else if(close.find(character) != std::string::npos)
        {
            if(bracketsStack.empty())
                return false;
            for(auto bracket : brackets)
            {
                if(bracket.second == character)
                {
                    if(bracketsStack.top() != bracket.first)
                        return false;
                    else
                        bracketsStack.pop();
                }
            }
        }
    }
    if(!bracketsStack.empty())
        return false;
    return true;
};