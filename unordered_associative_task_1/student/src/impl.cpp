#include "impl.h"
#include "set"

bool is_anagram(const std::string& first, const std::string& second)
{
    const std::multiset<char> first_word(first.begin(), first.end());
    const std::multiset<char> second_word(second.begin(), second.end());
    return first_word == second_word;
}
