#pragma once
#include <string>
using std::size_t;

/**
 * @todo Check if strings starts with another string
 *
 * @param source - input string
 * @param prefix - string assumed as prefix of source
 *
 * @return true if source starts from a prefix
 */
bool startsWith(const std::string& source, const std::string& prefix) {
    std::size_t isPrefixOf = source.find(prefix);
    return isPrefixOf != std::string::npos;
}
