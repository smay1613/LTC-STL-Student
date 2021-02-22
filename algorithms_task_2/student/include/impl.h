#pragma once
#include <string>
#include <algorithm>

/**
 * @todo Check if strings starts with another string
 *
 * @param source - input string
 * @param prefix - string assumed as prefix of source
 *
 * @return true if source starts from a prefix
 */
bool startsWith(const std::string& source, const std::string& prefix)
{
// possible solution:
//    int i = 0;
//    while (i < prefix.size() && prefix[i] == source[i]){++i;}
//    return i == prefix.length();

  if (prefix.size() > source.size())
      return false;

  return std::equal(prefix.begin(), prefix.end(), source.begin());
}
