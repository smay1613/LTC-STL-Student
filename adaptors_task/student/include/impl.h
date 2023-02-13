#pragma once
#include <string>
#include <stack>
/**
 * @todo isValid - check if given expression is valid - all open brackets are closed
 * by CORRESPONDING closed bracket.
 *
 * @param source - expression that will contain brackets
 * of three types: "()"/"[]"/"{}".
 * May contain other symbols or may not contain anything.
 *
 * @return true if expression is valid
 */

bool isValid(const std::string& source)
{
    std::stack<char> brackets;
    std::string close = ")]}";
    std::string open = "([{";
    for(int i = 0; i < source.size(); i++)
    {
        if(open.find(source[i]) != std::string::npos)
        {
            brackets.push(source[i]);
        }
        else if(close.find(source[i]) != std::string::npos)
        {
            if(brackets.empty())
                return false;
            switch(source[i])
            {
                case ')':
                {
                    if(brackets.top() != '(')
                        return false;
                    else
                        brackets.pop();
                    break;
                }
                case ']':
                {
                    if(brackets.top() != '[')
                        return false;
                    else
                        brackets.pop();
                    break;
                }
                case '}':
                {
                    if(brackets.top() != '{')
                        return false;
                    else
                        brackets.pop();
                    break;
                }
            } 
        }
    }
    if(!brackets.empty())
        return false;
    return true;
};
