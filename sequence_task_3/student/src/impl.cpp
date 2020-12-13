#include "impl.h"

std::string reverseWords(const std::string& input) {
    std::deque<std::string> strDeq;
    std::string world;
    std::string result;
    std::stringstream myString(input);

    while (myString >> world) {
        strDeq.push_front(world);
        strDeq.push_front(" ");
    }

    return result;
}
