#include "impl.h"
#include <vector>
#include<iostream>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source)
{
    std::stack<char> br_stack;

    auto isBracketClosed = [](const char ch ,const std::pair<char, char> bracket)
    {
        return ch==bracket.second;
    };

    for(const char &ch : source)
    {

        for(const auto &bracket : brackets )
        {
            if(br_stack.empty() && isBracketClosed(ch,bracket))
            {
                return false;
            }

            if(ch==bracket.first)
            {
                br_stack.push(ch);
            }

            if(!br_stack.empty() && isBracketClosed(ch,bracket))
            {
                auto lastBracketOpen = br_stack.top();
                if(lastBracketOpen != bracket.first)
                {
                    return false;
                }
                br_stack.pop();
            }
        }
    }
    return br_stack.empty();
}
