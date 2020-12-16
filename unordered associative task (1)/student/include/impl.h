#pragma once
#include <string>
#include <map>

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

bool is_anagram(const std::string& first, const std::string& second){
    std::map<char,int> charMap;
    for (char currentChar : first) {
        auto iterator = charMap.lower_bound(currentChar);
        if (iterator == charMap.end())
            charMap[currentChar] = 1;
        else
            charMap[currentChar] = charMap[currentChar] + 1;
    }
    for (char currentChar : second) {
        auto iterator = charMap.lower_bound(currentChar);
        if (iterator == charMap.end())
            return false;
        else
            charMap[currentChar] = charMap[currentChar] - 1;
    }
    for (auto i : charMap) {
        if(i.second != 0)
            return false;
    }
    return true;
}
