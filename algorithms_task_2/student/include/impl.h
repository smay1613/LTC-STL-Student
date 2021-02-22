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
bool startsWith(const std::string& source, const std::string& prefix) {
    if (prefix.length() > source.length()) {
        return false;
    }

    return std::equal(prefix.cbegin(), prefix.cend(), source.cbegin());
}
