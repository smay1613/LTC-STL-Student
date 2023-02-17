#pragma once
#include <sstream>
#include <iterator>
#include <string>

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

    std::string res, word;

    ss >> word;
    res = word;

    while (ss >> word) {
        res = word + " " + res;
    }

    return res;
}
