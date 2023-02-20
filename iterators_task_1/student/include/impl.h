#pragma once
#include <sstream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>

/**
 * @todo Implement function that will reverse words in a sentence
 * @example "Hello there" -> "there Hello"
 * @param input - sentence with words splitted by spaces
 * @return Sentence with reversed order of words
 *
 * @warning YOU MUST USE STRING STREAMS AND STREAM ITERATORS!
 */
std::string reverseWords(const std::string& input) {
    std::stringstream stream(input);
    std::vector<std::string> tokens;

    std::copy(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(), std::back_inserter(tokens));
    if(tokens.empty()) {
        return "";
    }
    std::string reversed_sentence;
    for_each(tokens.rbegin(), tokens.rend(), [&reversed_sentence](const std::string& item){reversed_sentence += item + " ";});
    reversed_sentence.pop_back();
    return reversed_sentence;
}
