#include "impl.h"
#include <vector>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source){
    std::stack<char> valid;

    for(const char & c : source){
        
        for(const auto & b : brackets ){
            if(c==b.second && valid.empty()){
                return false;
            }

            if(c==b.first){
                valid.push(c);
                break;
            }

            if(c==b.second && !valid.empty() ){
                auto popped = valid.top();
                if(popped!=b.first){
                    return false;
                }
                valid.pop();
            }
            
        }
    
    }

    return valid.empty();


}