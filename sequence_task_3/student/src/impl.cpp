#include "impl.h"
#include <sstream>
#include <iterator>
#include <numeric>

std::string reverseWords(const std::string& input)
{
    std::istringstream iss(input);

    auto res = std::accumulate(std::istream_iterator<std::string>(iss), 
                               std::istream_iterator<std::string>(), 
                               std::string(),
                               [](std::string a, std::string b) { return b + " " + a; });
    
    if(true != res.empty()) res.pop_back();

    return res;
}