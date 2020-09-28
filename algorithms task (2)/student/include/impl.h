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

// 1st solution
bool startsWith(const std::string& source, const std::string& prefix)
{
    return std::equal(prefix.begin(), prefix.end(), source.begin());
}

// 2nd solution
// bool startsWith(const std::string& source, const std::string& prefix)
// {
//     return (prefix.size() > source.size()) ? std::equal(source.begin(), source.begin() + prefix.size(), prefix.begin()) : false;
// }

// 3rd solution
// bool startsWith(const std::string& source, const std::string& prefix)
// {
//     auto mismatchPoint = std::mismatch(source.begin(), source.end(), prefix.begin());
//     return prefix.end() == mismatchPoint.second;
// }
