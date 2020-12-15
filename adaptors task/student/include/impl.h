#pragma once
#include <string>
#include <stack>
#include <vector>
#include <utility>
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
bool isOpenBracket(char ch, std::vector< std::pair <char,char> >& vector){
    bool isOpen = false;
    for(int j=0; j< vector.size();++j){
        if(ch == vector[j].first)
            isOpen = true;
    }
    return isOpen;
}

bool isClosedBracket(char ch, std::vector< std::pair <char,char> >& vector){
    bool isOpen = false;
    for(int j=0; j< vector.size();++j){
        if(ch == vector[j].second)
            isOpen = true;
    }
    return isOpen;
}

char correspondingClosedBracket(char ch, std::vector< std::pair <char,char> >& vector){
    for(int j=0; j< vector.size();++j){
        if(ch == vector[j].first)
            return vector[j].second;
    }
}
bool isValid(const std::string& source){
    std::stack<char> bracketsStack;
    std::vector< std::pair <char,char> > bracketsVector;

    bracketsVector.push_back(std::make_pair('(',')'));
    bracketsVector.push_back(std::make_pair('{','}'));
    bracketsVector.push_back(std::make_pair('[',']'));

    bool isValid = true;
    int lenght = source.size();
    for(int i=0; i<lenght; i++){
        char currentChar = source[i];
        if(isOpenBracket(currentChar, bracketsVector))
            bracketsStack.push(currentChar);
        else {
            if(!isClosedBracket(currentChar, bracketsVector))
                continue;
            else {
                if(bracketsStack.empty()) {
                    isValid = false;
                    break;
                }
                char hab = bracketsStack.top();
                char closedBracket = correspondingClosedBracket(hab,bracketsVector);
                if(closedBracket == currentChar)
                    bracketsStack.pop();
                else {
                    isValid = false;
                    break;
                }
            }
        }
    }
    if(!bracketsStack.empty())
        isValid= false;
    return isValid;
}
