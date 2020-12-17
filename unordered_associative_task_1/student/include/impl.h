#pragma once
#include <string>
#include <set>

/**
 * @todo Implement function that will check if one string has the same characters
 * as the second one
 *
 * @example is_anagram("abcd", "acdb") -> true
 * @example is_anagram("abcd", "abec") -> false
 *
 * @param first - first word
 * @param second - second word
 * @return true if first is anagram of second
 */
bool is_anagram(const std::string& first, const std::string& second)
{
    std::multiset<char> first_mset;
    std::copy(first.begin(),
              first.end(),
              std::inserter(first_mset, first_mset.end()));

    std::multiset<char> second_mset;
    std::copy(second.begin(),
              second.end(),
              std::inserter(second_mset, second_mset.end()));

    if(first_mset == second_mset)
        return true;
    else
        return false;
}
