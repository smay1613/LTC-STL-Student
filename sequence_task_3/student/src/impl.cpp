#include "impl.h"

std::string reverseWords(const std::string& input)
{
    std::istringstream input_stream(input);
    std::deque<std::string> words;
    std::move(std::istream_iterator<std::string>(input_stream),
              std::istream_iterator<std::string>(),
              std::front_inserter(words));

    std::ostringstream output_stream;
    std::move(words.begin(), words.end(),
              std::ostream_iterator<std::string>(output_stream, " "));
    std::string str(output_stream.str());
    if(!str.empty())
    {
        str.pop_back();
    }
    return str;
}
