#include "impl.h"
#include <unordered_set>

bool is_anagram(const std::string &first, const std::string &second)
{
    const std::unordered_multiset<char> firstCharset{first.cbegin(), first.cend()};
    const std::unordered_multiset<char> secondCharset{second.cbegin(), second.cend()};

    return firstCharset == secondCharset;
}
