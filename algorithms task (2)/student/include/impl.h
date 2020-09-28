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
    if (prefix.size() > source.size())
    {
        return false;
    }
    auto lastSource = source.begin() + prefix.size();
    return std::equal(source.begin(), lastSource, prefix.begin());
}
