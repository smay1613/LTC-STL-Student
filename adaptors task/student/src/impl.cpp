#include "impl.h"
#include <vector>
#include <stack>
const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source){
    if(source.size()==1){return false;}
    std::stack<char> checkString;

    for (auto currentChar : source) {
        for (auto bracket : brackets) {
            if (currentChar == bracket.first)
            {
                checkString.push(currentChar);
                continue;
            }
            else if (currentChar == bracket.second)
            {
                if (checkString.empty() or checkString.top() != bracket.first)
                {
                    return false;
                }
                checkString.pop();
                continue;
            }
        }
    }
    return checkString.empty();
}
