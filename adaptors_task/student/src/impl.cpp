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

bool add_or_fail(std::stack<char>& openBrackets, char& c ){
    auto is_opening_bracket = [c] (const std::pair<char,char>& b) { return c == b.first;};
    auto is_closing_bracket = [c] (const std::pair<char,char>& b) { return c == b.second;};

    if(std::find_if(brackets.begin(), brackets.end(),is_closing_bracket)!= brackets.end()){
        return false;
    }

    if(std::find_if(brackets.begin(), brackets.end(),is_opening_bracket)!= brackets.end()){
        openBrackets.push(c);
    }

    return true;
}

bool isValid(const std::string& source){
    std::stack<char> openBrackets;

    for(auto c : source){

        if( !openBrackets.empty()){
            auto bracket_pair = std::find(brackets.begin(), brackets.end(), std::make_pair(openBrackets.top(), c));

            const bool closeable_with_current_character = bracket_pair != brackets.end();

            if(closeable_with_current_character){
                
                openBrackets.pop();

            } else {
                const bool still_valid = add_or_fail(openBrackets, c);

                if(!still_valid){
                    return false;
                }
            }
        } else {
            const bool still_valid = add_or_fail(openBrackets, c);

            if(!still_valid){
                return false;
            }
        }
    }

    return openBrackets.empty();
}