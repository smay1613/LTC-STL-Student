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
        std::stringstream inputString(input);
        const std::deque<std::string> sentence { std::istream_iterator<std::string>(inputString), std::istream_iterator<std::string>() };
        std::stringstream outputString;
        std::copy(sentence.rbegin(), sentence.rend(), std::ostream_iterator<std::string>(outputString, " "));
        std::string str;
        str = outputString.str();

        if (!str.empty())
            {
                str.pop_back();
            }

        return str;
    }
