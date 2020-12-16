#include "impl.h"
#include "unordered_set"

bool is_anagram(const std::string& first, const std::string& second)
{
    const std::unordered_multiset<char> set_f(first.begin(), first.end());
    const std::unordered_multiset<char> set_s(second.begin(), second.end());
    return set_f == set_s;
}
