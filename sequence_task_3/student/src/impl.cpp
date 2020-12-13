#include "impl.h"
#include <algorithm>

std::string reverseWords(const std::string& input)
{
    std::stringstream istream(input);
    std::deque<std::string> deque;

    std::for_each(std::istream_iterator<std::string>(istream), std::istream_iterator<std::string>(), [&deque]( const std::string& s )
    {
        deque.push_front(s);
    });

    std::stringstream outstream;
    std::for_each(deque.begin(), deque.end(), [&outstream, &deque]( const std::string& word )
    {
        outstream << word;
        if (word != deque.back())
        {
            outstream << ' ';
        }
    });

    return outstream.str();
}

