#include "impl.h"
#include <unordered_set>

bool is_anagram(const std::string& first, const std::string& second) {

    return std::unordered_multiset<char>(first.cbegin(), first.cend()) ==
           std::unordered_multiset<char>(second.cbegin(), second.cend());
}
