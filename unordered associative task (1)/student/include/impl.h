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
bool is_anagram(const std::string& first, const std::string& second){
  if (first.size() != second.size()) return false;
  else {
    std::unordered_multiset<char> lhs;
    std::unordered_multiset<char> rhs;
    for (size_t i = 0; i < first.size(); i++) {
      lhs.insert(first[i]);
      rhs.insert(second[i]);
    }
    return lhs == rhs;
  }
}
