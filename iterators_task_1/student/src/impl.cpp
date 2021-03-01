#include "impl.h"

std::string reverseWords(const std::string& input)
{
    std::stringstream inputStream{input};

    std::vector<std::string> parsed{std::istream_iterator<std::string>(inputStream),
                std::istream_iterator<std::string>()};

    std::stringstream outputStream;
    std::reverse_copy(parsed.begin(), parsed.end(), std::ostream_iterator<std::string>{outputStream, " "});

    std::string merged{outputStream.str()};
    if(!merged.empty())
        merged.pop_back();

    return merged;
}
