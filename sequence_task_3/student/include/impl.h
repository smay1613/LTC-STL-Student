#pragma once
#include <sstream>
#include <deque>
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
std::string reverseWords(const std::string& input)
{
    std::istringstream iss(input);
    std::vector<std::string> words(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
    std::string result = "";

    std::reverse(words.begin(),words.end());

    std::ostringstream ss;
    std::copy(words.begin(),words.end(), std::ostream_iterator<std::string>(ss, " "));
    result = ss.str();

    if (result.size() > 0)
        result.erase(result.end() - 1);
    return result;
}
