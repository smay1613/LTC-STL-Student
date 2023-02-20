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
bool startsWith(const std::string& source, const std::string& prefix){
    return source.find(prefix, 0) == 0;
    // Can also check source.begin() == std::search(source.begin(), source.end(), prefix.begin(), prefix.end());
    // Another possibility is std::mismatch
    // Could also check if std::equal(source.begin(), std::next(source.begin(), prefix.size), prefix.begin(), prefix.end()) is true 
    // Or check if source.substr(0, prefix.size()) == prefix
}
