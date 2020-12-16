#include "impl.h"

std::string reverseWords(const std::string& input)
{
    std::string ret;
    if(!input.empty())
    {
        std::stringstream in(input);
        const std::deque<std::string> ds { std::istream_iterator<std::string>(in), std::istream_iterator<std::string>() };
        std::stringstream out;
        std::copy(ds.rbegin(), ds.rend(), std::ostream_iterator<std::string>(out, " "));
        ret = out.str();

        if (!ret.empty())
        {
            ret.pop_back();
        }
    }
    return ret;
}

