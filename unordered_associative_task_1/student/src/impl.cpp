#include "impl.h"
#include <unordered_set>

bool is_anagram(const std::string& first, const std::string& second)
{
    std::unordered_multiset<char> firstSet(first.begin(), first.end(), first.size());
    std::unordered_multiset<char> secondSet(second.begin(), second.end(), second.size());

    return firstSet == secondSet;
}
