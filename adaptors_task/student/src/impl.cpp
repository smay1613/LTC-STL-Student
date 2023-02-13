#include "impl.h"
#include <vector>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string &source) {
    std::stack<char> notClosedBr;
    for (char c : source) {
        switch(c) {
            case '(':
            case '[':
            case '{':
                notClosedBr.push(c);
                break;
            case ')':
                if(notClosedBr.empty() || notClosedBr.top() != brackets.at(0).first) {
                    return false;
                }
                notClosedBr.pop();
                break;
            case ']':
                if(notClosedBr.empty() || notClosedBr.top() != brackets.at(1).first) {
                    return false;
                }
                notClosedBr.pop();
                break;
            case '}':
                if (notClosedBr.empty() || notClosedBr.top() != brackets.at(2).first) {
                    return false;
                }
                notClosedBr.pop();
                break;
            default:
                break;
        }
    }
    return notClosedBr.empty();
}
