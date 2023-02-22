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
     return source.rfind(prefix, source.find_first_not_of(' ')) == 0; // ignore initial whitespaces
     //return source.rfind(prefix, 0) == 0;                           // string must start without whitespaces
     //return source.find(prefix) == 0;                               // prefix must be at beginning of source
}
