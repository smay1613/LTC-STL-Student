#include "impl.h"
#include <vector>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};


bool isValid(const std::string& source) {
    std::stack<char> s;

    auto secondBracket = [] (char firstBracket) {
         for(auto i : brackets) {
             if(i.second == firstBracket) return i.first;
         };
         return('!');
    };

    auto isBracket = [] (char ch) {
        return ch == ']' || ch == '}' || ch == ')' || ch == '[' || ch == '{' || ch == '(';
    };

    for(char ch : source) {
        if (isBracket(ch)) {
            if(!s.empty() && s.top() == secondBracket(ch))
                s.pop();
            else s.push(ch);
        }
    }
    return s.empty();
}
