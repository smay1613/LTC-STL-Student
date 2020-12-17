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
    std::stack<char> s;

    for(const char& i: source) {
        switch (i) {
            case '[':
                s.push(']');
                break;
            case ']': {
                if(s.empty())
                    return false;

                char c = s.top();
                if(c == ']') {
                    s.pop();
                    break;
                } else {
                    return false;
                }
            }
            case '{':
                s.push('}');
                break;
            case '}': {
                if(s.empty())
                    return false;

                char c = s.top();
                if(c == '}') {
                    s.pop();
                    break;
                } else {
                    return false;
                }
            }
            case '(':
                s.push(')');
                break;
            case ')': {
                if(s.empty())
                    return false;

                char c = s.top();
                if(c == ')') {
                    s.pop();
                    break;
                } else {
                    return false;
                }
            }
        }
    }

    if(!s.empty())
        return false;

    return true;
}
