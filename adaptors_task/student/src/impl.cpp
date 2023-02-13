#include "impl.h"
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

struct isBracket
{
  isBracket(char _c) : c(_c) {}
  bool operator()(const std::pair<char,char>& bracketPair) const {
    return c == bracketPair.first || c == bracketPair.second;
  }
  private:
    char c;
};

bool isValid(const std::string& source){
    std::stack<char> openBrackets;

    for(auto c : source){
        const bool closeable_with_current_character = !openBrackets.empty() && 
        std::find(brackets.begin(), brackets.end(), std::make_pair(openBrackets.top(), c)) != brackets.end();

        if(openBrackets.empty() || !closeable_with_current_character){
            
            if(std::find_if(brackets.begin(), brackets.end(), isBracket(c)) != brackets.end()){
                openBrackets.push(c);
            }

        } else {

            openBrackets.pop();

        }

    }

    return openBrackets.empty();
}