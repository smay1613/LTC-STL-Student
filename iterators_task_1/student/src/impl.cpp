#include "impl.h"
#include "vector"

std::string reverseWords(const std::string& input){
    std::istringstream stream {input};
    std::vector<std::string> words{std::istream_iterator<std::string> {stream},
                                   std::istream_iterator<std::string> {}};
    std::ostringstream out;
    std::copy(words.rbegin(), words.rend(), std::ostream_iterator<std::string>{out, " "});
    auto result=out.str();
    result.pop_back();
    return result;
}
