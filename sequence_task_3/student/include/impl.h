#pragma once
#include <algorithm>
#include <deque>
#include <iterator>
#include <sstream>

/**
 * @todo Implement function that will reverse words in a sentence
 * @example "Hello there" -> "there Hello"
 * @param input - sentence with words splitted by spaces
 * @return Sentence with reversed order of words
 *
 * @warning YOU MUST USE STRING STREAMS AND STREAM ITERATORS!
 */
std::string reverseWords(const std::string& input)
{
    std::istringstream iss(input);
    std::deque<std::string> words;
    for_each(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
        [&words](const std::string& word) { words.push_front(word); });

    std::ostringstream oss;
    std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(oss, " "));
    std::string result { oss.str() };
    if (!result.empty()) {
        result.resize(result.size() - 1);
    }
    return result;
}
