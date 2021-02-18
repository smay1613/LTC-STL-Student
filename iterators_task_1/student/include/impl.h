#pragma once
#include <sstream>
#include <iterator>
#include <string>

/**
 * @todo Implement function that will reverse words in a sentence
 * @example "Hello there" -> "there Hello"
 * @param input - sentence with words splitted by spaces
 * @return Sentence with reversed order of words
 *
 * @warning YOU MUST USE STRING STREAMS AND STREAM ITERATORS!
 */
std::string reverseWords(const std::string& input);

class TokenString{
public:
    const std::string& getToken() const;
    std::string& getToken();
    bool isEmpty() const;
private:
    std::string m_data;
};

std::istream& operator>>(std::istream& stream, TokenString& token){
    std::getline(stream, token.getToken(), ' ');
    return stream;
}