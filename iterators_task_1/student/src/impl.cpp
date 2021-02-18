#include "impl.h"

#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>


std::string reverseWords(const std::string& input)
{
    if (input.empty())
    {
        return {};
    }

    std::istringstream inputStream {input};
    std::vector<std::string> container { std::istream_iterator<std::string>(inputStream),
                                         std::istream_iterator<std::string>() };

    if (container.empty())
    {
        return {};
    }

    std::ostringstream outputStream;
    auto rbegin = container.rbegin();
    auto rend = container.rend();
    std::copy(rbegin, std::prev(rend), std::ostream_iterator<std::string>(outputStream, " "));
    outputStream << container.front();

    return outputStream.str();
}
