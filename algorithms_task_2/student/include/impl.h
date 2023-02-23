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
    if( source.size() < prefix.size()){
        return false;
    }
    return std::equal(source.begin(), std::next(source.begin(), prefix.size()), prefix.begin());
    // std::equal shortcitcuits on first getting unequal value so it will be faster in most cases than O(prefix.size)
    // Checking source.find(prefix, 0, prefix.size()) == 0 will be liniar in prefix size, so it's slower in some cases
    // Can also check source.begin() == std::search(source.begin(), source.end(), prefix.begin(), prefix.end()); 
    // but will also check whole source first
    // Could also check if std::mismatch(source.begin(), std::next(source.begin(), prefix.size), prefix.begin(), prefix.end()) 
    // is a pair of source begin + prefix size and prefix end, worse readability than equal and additional memory for pair  
    // Or check if source.substr(0, prefix.size()) == prefix, liniar in prefix size for substring copy
}
