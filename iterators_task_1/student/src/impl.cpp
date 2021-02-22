#include "impl.h"

#include <vector>
#include <algorithm>
#include <iostream>

std::string reverseWords(const std::string& input)
{
    using ii_string = std::istream_iterator<std::string>;
    using oi_string = std::ostream_iterator<std::string>;

    std::istringstream iss {input};
    std::vector<std::string> words {ii_string{iss}, ii_string{}};

    if (words.empty()) {
        return "";
    }

    std::stringstream result;
    std::copy(words.rbegin(), words.rend(), oi_string(result, " "));
    std::string str_result {result.str()};
    str_result.pop_back();

    return str_result;
}
