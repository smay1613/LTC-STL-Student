#pragma once
#include <sstream>
#include <iterator>

/**
 * @todo Implement function that will reverse words in a sentence
 * @example "Hello there" -> "there Hello"
 * @param input - sentence with words splitted by spaces
 * @return Sentence with reversed order of words
 *
 * @warning YOU MUST USE STRING STREAMS AND STREAM ITERATORS!
 */
std::string reverseWords(const std::string& input) {
    std::stringstream myStream(input);
    std::string token, reversedSentence;
    while(myStream >> token) {
        reversedSentence = " " + token + reversedSentence;
    }
    if (reversedSentence.empty()) {
        return "";
    }
    return reversedSentence.substr(1);
}
