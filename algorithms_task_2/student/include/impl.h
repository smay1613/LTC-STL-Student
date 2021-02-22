#pragma once
#include <string>

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
    if (prefix.empty())
    {
        return true;
    }

    if (prefix.size() > source.size())
    {
        return false;
    }

    return std::equal(std::begin(prefix), std::end(prefix), std::begin(source));
}
