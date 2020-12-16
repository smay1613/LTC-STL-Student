#include "impl.h"
#include "unordered_set"

bool is_anagram(const std::string& first, const std::string& second)
{
    std::unordered_multiset<char> const set_f(first.begin(), first.end());
    std::unordered_multiset<char> const set_s(second.begin(), second.end());
    return set_f == set_s;
}
