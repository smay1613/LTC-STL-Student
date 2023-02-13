#include "impl.h"
#include <vector>
#include <stack>
#include <tuple> 

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

enum class KindOfChar {OpenBracket, ClosedBracket, NoBracket};

std::pair<KindOfChar,  char> Find_KindOfChar_CorrespondingBracket(const char & c){
    for(const auto & b : brackets ){
         if(c==b.first){
            return std::make_pair(KindOfChar::OpenBracket, b.second);
         }

         if (c==b.second){
            return std::make_pair(KindOfChar::ClosedBracket, b.first);
         }

        
    }

     return std::make_pair(KindOfChar::NoBracket,'\0');

};

bool isValid(const std::string& source){

    std::stack<char> StackOfOpenBrackets;

    for(const char & c : source){

        KindOfChar KindOfc;
        char CorrespondingBracket;

        std::tie( KindOfc, CorrespondingBracket) = Find_KindOfChar_CorrespondingBracket (c);

        switch (KindOfc){
            case KindOfChar::OpenBracket :
                StackOfOpenBrackets.push(c);
                break;
            case KindOfChar::ClosedBracket :
                if(StackOfOpenBrackets.empty()){
                    return false;
                } else {
                    auto LastOpenBracket = StackOfOpenBrackets.top();
                    if(LastOpenBracket!=CorrespondingBracket){
                        return false;
                    }
                    StackOfOpenBrackets.pop();
                }
                break;

            case KindOfChar::NoBracket:
                break;   
        
        }
    }

    return StackOfOpenBrackets.empty();


}