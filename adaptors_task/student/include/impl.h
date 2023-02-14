#pragma once
#include <string>
#include <stack>

using namespace std;

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
bool isValid(const std::string& source){
    stack <string> openingbrackets;
    for (const char ch : source){
        switch (ch)
        {
        case '(':
        case '{':
        case '[':
            openingbrackets.push(&ch);
            break;

        case ')':
            if (openingbrackets.empty() || openingbrackets.top() != "("){
                return false;
            }
            openingbrackets.pop();
            break;
        
        case '}':
            if (openingbrackets.empty() || openingbrackets.top() != "{"){
                return false;
            }
            openingbrackets.pop();
            break;
        
        case ']':
            if (openingbrackets.empty() || openingbrackets.top() != "["){
                return false;
            }
            openingbrackets.pop();
            break;

        default:
            break;
        }
    }

    return openingbrackets.empty();
}