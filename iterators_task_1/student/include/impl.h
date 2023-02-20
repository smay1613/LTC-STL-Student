#pragma once
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

/**
 * @todo Implement function that will reverse words in a sentence
 * @example "Hello there" -> "there Hello"
 * @param input - sentence with words splitted by spaces
 * @return Sentence with reversed order of words
 *
 * @warning YOU MUST USE STRING STREAMS AND STREAM ITERATORS!
 */
std::string reverseWords(const std::string& input){
    std::stringstream in{input};
    std::vector<std::string> token{std::istream_iterator<std::string> {in},std::istream_iterator<std::string> {}};
    
    if(token.empty()){
        return "";
    }

    std::stringstream out{};
    std::copy(token.rbegin(),token.rend(),std::ostream_iterator<std::string> {out, " "});
    
    std::string result=out.str();

    if(!result.empty()){
        result.pop_back();
    }
    
    return result;
}
