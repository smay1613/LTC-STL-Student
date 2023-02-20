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
    return std::equal(prefix.begin(),prefix.end(),source.begin()); // Complexity: prefix.begin()-prefix.end() applications of the predicate

    // Alternatives:
    // return source.find(prefix)==0; Complexity: Unspecified, but generally up to linear in length()-pos times the length of the sequence to match (worst case)
    //return std::search(source.begin(),source.end(),prefix.begin(),prefix.end())==source.begin();
}
