#pragma once
#include <sstream>
#include <iterator>
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
    std::stringstream Stream(input);
    std::stringstream Out;
    std::istream_iterator<std::string> begin(Stream);
    std::istream_iterator<std::string> end;
    std::vector<std::string> words(begin, end);
    if(words.empty())
    {
        return "";
    }
    std::copy( words.rbegin(),words.rend(), std::ostream_iterator<std::string>(Out, " "));
    std::string reversed = Out.str();
    reversed.pop_back();
    return reversed;
}
