#include "impl.h"
#include <iostream>

std::string reverseWords(const std::string& input)
{
    std::string tmp;
    std::deque<std::string> words;
    std::stringstream  ss{input};
    while (ss >> tmp)
    {
        words.push_front(tmp);
    }
    std::stringstream  ss1;
    for(auto& word: words )
    {
        ss1 << word;
        if (word != words.back())
        {
            ss1 << ' ';
        }
    }
    return ss1.str();
}
