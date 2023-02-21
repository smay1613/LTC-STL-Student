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
    return std::mismatch(source.begin(), std::next(source.begin(), prefix.size()), prefix.begin()) == make_pair(std::next(source.begin(), prefix.size()), prefix.end());
    // Checking source.find(prefix, 0, prefix.size()) == 0 will be liniar in prefix size, so it's slower in some cases
    // Can also check source.begin() == std::search(source.begin(), source.end(), prefix.begin(), prefix.end());
    // Could also check if std::equal(source.begin(), std::next(source.begin(), prefix.size), prefix.begin(), prefix.end()) is true 
    // Or check if source.substr(0, prefix.size()) == prefix
}
