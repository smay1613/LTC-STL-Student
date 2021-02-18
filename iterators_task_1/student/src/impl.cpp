#include "impl.h"
#include <deque>

std::string reverseWords(const std::string& input)
{
    std::stringstream inputStream{input};
    std::stringstream outputStream;
    std::deque<std::string> inputStrList;

    std::copy(std::istream_iterator<std::string>{inputStream}, std::istream_iterator<std::string>{}, std::front_inserter(inputStrList));
    std::copy(inputStrList.begin(), inputStrList.end(), std::ostream_iterator<std::string>{outputStream, " "});

    std::string uotput {outputStream.str()};
    uotput.pop_back();

    return uotput;
}
