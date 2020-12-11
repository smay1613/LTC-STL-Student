#include "impl.h"
#include <algorithm>


std::string reverseWords(const std::string& input)
{
    std::istringstream ss(input);

    std::deque<std::string> strDeque;

    std::for_each(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>(),
        [&strDeque](const std::string& str){
            strDeque.push_front(str);
        });

    std::ostringstream oss;
    for (auto word : strDeque) {
        oss << " " << word;
    }
    std::string result = oss.str();

    if(result.size() > 0) {
        return {std::next(result.begin()), result.end()};
    } else {
        return result;
    }
}
