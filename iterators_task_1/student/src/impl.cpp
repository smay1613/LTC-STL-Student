#include "impl.h"

std::string reverseWords(const std::string& input)
{
    std::stringstream stream{input};

    std::vector<std::string> parsed{std::istream_iterator<std::string>(stream),
                std::istream_iterator<std::string>()};

    stream = std::stringstream();
    std::reverse_copy(parsed.begin(), parsed.end(), std::ostream_iterator<std::string>{stream, " "});

    std::string merged{stream.str()};
    if(merged.length())
        merged.pop_back();

    return merged;
}
