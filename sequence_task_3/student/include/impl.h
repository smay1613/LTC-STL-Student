#pragma once
#include <sstream>
#include <deque>
#include <iterator>
#include <stack>

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
    std::stack<std::string> inputWords;
    std::string word;
    std::stringstream s(input);

    while (getline(s, word, ' ')) {
        if( word.size() != 0) {
            inputWords.push(word);
        }
    }

    std::string out("");
    while(!inputWords.empty()) {
        out += inputWords.top();
        inputWords.pop();

        if(!inputWords.empty()) {
            out += " ";
        }
    }

    return out;
}
