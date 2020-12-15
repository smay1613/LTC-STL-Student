#include "impl.h"
#include <vector>
#include <stack>
#include <utility>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isOpenBracket(char ch) {
    for (auto v : brackets) {
        if(ch == v.first)
            return true;
    }
    return false;
}

bool isClosedBracket(char ch) {
    for (auto v : brackets) {
        if(ch == v.second)
            return true;
    }
    return false;
}

char correspondingClosedBracket(char ch) {
    for (auto v : brackets) {
        if(ch == v.first)
            return v.second;
    }
}

bool isValid(const std::string& source){
    std::stack<char> bracketsStack;

    for(char currentChar : source){
        if(isOpenBracket(currentChar))
            bracketsStack.push(currentChar);
        else {
            if(!isClosedBracket(currentChar))
                continue;
            else {
                if(bracketsStack.empty())
                    return false;

                char currentOpenBracket = bracketsStack.top();
                char closedBracket = correspondingClosedBracket(currentOpenBracket);
                if(closedBracket == currentChar)
                    bracketsStack.pop();
                else
                    return false;
            }
        }
    }
    return bracketsStack.empty();
}
