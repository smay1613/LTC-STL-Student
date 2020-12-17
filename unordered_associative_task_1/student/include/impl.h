#pragma once
#include <string>
#include <unordered_set>

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
    std::unordered_multiset<char> unordered_mset;
    std::copy(first.begin(),
              first.end(),
              std::inserter(unordered_mset, unordered_mset.end()));

    for(const char& c: second) {

        if(unordered_mset.empty())
            return false;

        auto search = unordered_mset.find(c);
        if (search != unordered_mset.end()) {
            unordered_mset.erase(search);
        } else {
            return false;
        }
    }
    if(unordered_mset.empty())
        return true;
    else
        return false;
}
