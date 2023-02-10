#include "impl.h"
#include <vector>
#include <stack>
#include <iostream>
const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source){
    std::stack<char> notClosed;

    for(auto i = 0; i < source.size(); i++){
        bool closed = false;

        if(!notClosed.empty()){
            for(auto b : brackets){
                if(std::make_pair(notClosed.top(), source[i]) == b){
                    notClosed.pop();
                    closed = true;
                    break;
                }  
            }
        }
        
        if(!closed){
            for( auto b : brackets){
                if(source[i] == b.first || source[i] == b.second){
                    notClosed.push(source[i]);
                }
            }
        }
    }

    return notClosed.empty();
}