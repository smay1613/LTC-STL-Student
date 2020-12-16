#include "impl.h"
#include <algorithm>

std::string reverseWords(const std::string& input)
{
    std::stringstream istream(input);
    std::deque<std::string> deque { std::istream_iterator<std::string>(istream), std::istream_iterator<std::string>() };

    std::stringstream outstream;
    std::ostream_iterator<std::string> iout(outstream, " ");
    std::copy(deque.rbegin(), deque.rend(), iout );

    std::string result = outstream.str();
    if (!result.empty())
    {
        result.pop_back();
    }
    return result;
}

