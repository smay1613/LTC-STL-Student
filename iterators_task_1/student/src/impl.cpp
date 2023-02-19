#include "impl.h"
#include <vector>

std::string reverseWords(const std::string& input) {
    std::stringstream get_words {input};
    const std::vector<std::string> words {std::istream_iterator<std::string> {get_words}, std::istream_iterator<std::string> {}};

    std::stringstream reverse_words {};
    std::copy(words.rbegin(), words.rend(), std::ostream_iterator<std::string> {reverse_words, " "});

    std::string output {reverse_words.str()};
    if (!output.empty()) {
        output.pop_back();
    }

    return output;
}
