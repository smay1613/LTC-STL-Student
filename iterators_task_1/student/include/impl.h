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
    std::stringstream streamInput(input);
    std::vector<std::string> tokenized(std::istream_iterator<std::string>{streamInput},
                                       std::istream_iterator<std::string>{});

    std::stringstream streamOutput{};
    std::copy(tokenized.rbegin(),tokenized.rend(),
                 std::ostream_iterator<std::string>{streamOutput," "});

    std::string merged{streamOutput.str()};

    if (!merged.empty())
        merged.pop_back();

    return merged;
};
