#include "impl.h"

#include <sstream>
#include <iterator>
#include <algorithm>
#include <list>


std::string reverseWords(const std::string& input)
{
    if (input.empty())
    {
        return {};
    }

    std::istringstream inputStream {input};
    std::ostringstream outputStream;
    std::list<std::string> container = {};

    std::copy(std::istream_iterator<std::string>(inputStream),
              std::istream_iterator<std::string>(),
              std::front_inserter(container));

    if (container.empty())
    {
        return {};
    }

    auto begin = std::begin(container);
    auto end = std::end(container);
    std::copy(begin, std::prev(end), std::ostream_iterator<std::string>(outputStream, " "));
    std::copy(std::prev(end), end, std::ostream_iterator<std::string>(outputStream));

    return outputStream.str();
}

//#include <vector>

//std::string reverseWords(const std::string& input)
//{
//    if (input.empty())
//    {
//        return {};
//    }

//    std::istringstream inputStream {input};
//    std::ostringstream outputStream;
//    std::vector<std::string> container { std::istream_iterator<std::string>(inputStream),
//                                         std::istream_iterator<std::string>() };

//    if (container.empty())
//    {
//        return {};
//    }

//    auto rbegin = container.rbegin();
//    auto rend = container.rend();
//    std::copy(rbegin, std::prev(rend), std::ostream_iterator<std::string>(outputStream, " "));
//    std::copy(std::prev(rend), rend, std::ostream_iterator<std::string>(outputStream));

//    return outputStream.str();
//}
