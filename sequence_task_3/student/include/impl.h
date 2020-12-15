#pragma once
#include <sstream>
#include <deque>
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

    std::istringstream ss(input);
    std::stringstream output;
    std::deque<std::string> newData;

    copy(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>(), front_inserter(newData));
    copy(newData.begin(), newData.end(), std::ostream_iterator<std::string>(output, " "));

    std::string result = output.str();

    if (!result.empty()) {
        result.erase(result.end() - 1);
    }

    return result;
}
