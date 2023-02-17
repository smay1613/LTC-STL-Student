#pragma once
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>

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
    std::vector<std::string> token;
    std::istringstream in(input);
    std::ostringstream out;
    
    std::move(
        std::istream_iterator<std::string>(in),
        std::istream_iterator<std::string>(),
        std::back_inserter(token)
    );

    if (token.empty())
        return "";

    std::copy(
        token.rbegin(), 
        token.rend(),
        std::ostream_iterator<std::string>(out, " ")
    );

    std::string result = out.str();

    return std::move(result.substr(0, result.length() - 1));
}
