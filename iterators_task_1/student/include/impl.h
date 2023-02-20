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
    std::istringstream iss(input);
    std::vector<std::string> words(std::istream_iterator<std::string>(iss), {});

    std::ostringstream oss;
    std::copy(words.rbegin(), words.rend(), std::ostream_iterator<std::string>(oss, " "));

    std::string reversed = oss.str();
    return reversed.substr(0, reversed.length() - 1);
}
