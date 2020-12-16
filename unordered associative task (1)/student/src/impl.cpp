#include "impl.h"
#include "unordered_map"

bool is_anagram(const std::string& first, const std::string& second)
{
    std::unordered_map<char, size_t> firstMap;
    std::unordered_map<char, size_t> secondMap;

    for (auto symbol: first) {
        firstMap[symbol]++;
    }

    for (auto symbol: second) {
        secondMap[symbol]++;
    }

    if (firstMap == secondMap) {
        return true;
    } else {
        return false;
    }
}
