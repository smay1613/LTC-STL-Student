#include "impl.h"
#include <algorithm>
#include <string>
#include <numeric>
#include <sstream>

std::string reverseWords(const std::string& input) {
    std::deque<std::string> dequeResultString;
    std::string world;
    std::stringstream inputString(input);

    for_each(std::istream_iterator<std::string>(inputString), std::istream_iterator<std::string>(),
        [&dequeResultString](const std::string& word) { dequeResultString.push_front(word);
                                                        dequeResultString.push_front(" ");});

    std::ostringstream outputString;

    std::copy(dequeResultString.rbegin(), dequeResultString.rend(),
                std::ostream_iterator<std::string>(outputString));

    std::string result(outputString.str());
    return result;
}
