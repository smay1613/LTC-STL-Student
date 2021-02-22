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
    if (prefix.empty()) {
        return prefix.empty() || source.empty();
    }
    if (prefix.size() > source.length()) {
        return false;
    }

    return std::equal(source.cbegin(), source.cbegin() + prefix.length(), prefix.cbegin());
}
