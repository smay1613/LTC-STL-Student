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
    return source.length() >= prefix.length() &&
           std::equal(prefix.begin(), prefix.end(), source.begin());
}

bool startsWith2(const std::string& source, const std::string& prefix)
{
    return source.length() >= prefix.length() &&
           std::mismatch(source.begin(), source.end(), prefix.begin()).second == prefix.end();
}
