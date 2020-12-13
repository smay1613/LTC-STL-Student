#include "impl.h"

#include <algorithm>

std::string reverseWords(const std::string& input) {
    std::istringstream istr(input);
    std::deque<std::string> deq{std::istream_iterator<std::string>(istr),
                                std::istream_iterator<std::string>()};
    std::ostringstream ostr;
    std::copy(deq.rbegin(), deq.rend(), std::ostream_iterator<std::string>(ostr, " "));
    std::string ret(ostr.str());
    if (!ret.empty())
        ret.pop_back();
    return ret;
}
