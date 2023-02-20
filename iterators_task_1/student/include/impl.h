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
    std::ostringstream output;
    std::copy(tokens.rbegin(), tokens.rend(), std::ostream_iterator<std::string>(output, " "));
    std::string reversed_sentence = output.str();
    reversed_sentence.pop_back();
    return reversed_sentence;
}
