#include "impl.h"
#include <vector>
#include <algorithm>


std::string reverseWords(const std::string &input)
{
    std::istringstream iss{input};
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

    if(tokens.empty())
        return "";

    std::ostringstream oss;
    std::copy(tokens.rbegin(), tokens.rend(), std::ostream_iterator<std::string>(oss, " "));

    std::string reverseString{oss.str()};
    reverseString.pop_back();

    return reverseString;
}
