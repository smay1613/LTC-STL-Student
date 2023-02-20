#pragma once
#include <sstream>
#include <iterator>
#include <string>
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
    std::stringstream ss(input);
    std::vector<std::string> words((std::istream_iterator<std::string>(ss)), std::istream_iterator<std::string>());

    std::ostringstream oss;
    std::copy(words.rbegin(), 
    words.rend(), 
    std::ostream_iterator<std::string>(oss, " "));
    
    std::string res(oss.str());
    if(!res.empty()){
        res.pop_back();
    }
    
    return res;
}
