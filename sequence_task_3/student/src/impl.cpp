#include "impl.h"


std::string reverseWords(const std::string &input)
{
    std::istringstream iss{input};
    std::deque<std::string> container{std::istream_iterator<std::string> {iss},
                                      std::istream_iterator<std::string> {}};

    std::ostringstream oss{};
    std::copy(container.rbegin(), std::prev(container.rend()), std::ostream_iterator<std::string>{oss, " "});
    oss << container.front();
    //not sure if this is the best way to avoid trailing space, but at least it's short and clear.

    return oss.str();
}
