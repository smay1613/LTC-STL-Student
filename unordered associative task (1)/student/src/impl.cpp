#include "impl.h"
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
   std::unordered_multiset<char> one{first.begin(), first.end()};
   std::unordered_multiset<char> two{second.begin(), second.end()};
   return one == two;
}
