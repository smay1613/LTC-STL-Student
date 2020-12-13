#pragma once
#include <sstream>
#include <deque>
#include <iterator>
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
    std::stringstream output;
    std::string res;
    std::istringstream ss(input);
    std::deque<std::string> cont;
    copy(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>(), front_inserter(cont));
    std::copy(cont.begin(), cont.end(), std::ostream_iterator<std::string>(output, " "));
    res = output.str();
    if (!res.empty()) {
        res.erase(res.end()-1);
    }
    return res;
}
