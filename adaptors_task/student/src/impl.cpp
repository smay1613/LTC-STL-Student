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

    for(const char &ch : source)
    {

        for(const auto &bracket : brackets )
        {
            if(br_stack.empty() && ch==bracket.second )
            {
                return false;
            }

            if(ch==bracket.first)
            {
                br_stack.push(ch);
                break;
            }

            if(!br_stack.empty() && ch==bracket.second)
            {
                auto first = br_stack.top();
                if(first != bracket.first)
                {
                    return false;
                }
                br_stack.pop();
            }
        }
    }
    return br_stack.empty();
}
