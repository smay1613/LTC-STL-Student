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

std::string reverseString(const std:: string& input){
    if (input.size() <= 1){
        return input;
    }
    return input.back() + reverseString(input.substr(0, input.size() - 1));
}

void reduce_space(std::ostringstream& oss, std::stringstream& ss, char prev){
    char curr;
    if (ss.get(curr)){
        if(std::isspace(curr)){
            if(!std::isspace(prev)){
                oss.put(' ');
            }
            reduce_space(oss, ss, curr);
        }else {
            oss.put(curr);
            reduce_space(oss, ss, curr);
        }
    }
}

std::string reverseWords(const std::string& input){
    std::istringstream iss(input);
    std::string word;

    iss >> word;

    if (!iss) {
        return "";
    }

    std::string output = word + std::string(std::istream_iterator<char>(iss), std::istream_iterator<char>());
    
    std::stringstream ss(output);
    std::string reversed_output = std::string(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>());
    std::string final_output = reverseString(reversed_output);


    std::stringstream ss2(final_output);
    std::ostringstream oss;
    char prev = '\0';
    reduce_space(oss, ss2, prev);
    return oss.str();

}
