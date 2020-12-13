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
std::string reverseWords(const std::string& input)
{
    std::istringstream iss(input);
    std::ostringstream oss;
    std::deque<std::string> strings((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    for (auto it = strings.rbegin(); it != strings.rend(); ++it)
    {
      oss << *it;
      if(std::next(it) != strings.rend()) oss << " ";
    }
    return oss.str();
}
