#include "impl.h"
#include <algorithm>
#include <string>
#include <numeric>
#include <iostream>

std::string reverseWords(const std::string& input) {
    std::deque<std::string> strDeq;
    std::string world;
    std::stringstream myString(input);

    while (myString >> world) {
        strDeq.push_front(world);
        strDeq.push_front(" ");
    }

    std::string result = std::accumulate(strDeq.begin(), strDeq.end(), result);
    return result;
}
