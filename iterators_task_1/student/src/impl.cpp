#include "impl.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

std::string reverseWords(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> vStr{std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>()};
    std::reverse(std::begin(vStr), std::end(vStr));
    std::string str {};

    std::all_of(vStr.begin(), vStr.end() - 1,[&str](const std::string& s) {
                                           str += s;
                                           str += " ";
                                           return true;
                                       });
    str += vStr.back();
    return str;
}
