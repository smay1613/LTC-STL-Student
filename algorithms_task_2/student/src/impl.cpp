#include "impl.h"
#include <algorithm>

bool startsWith(const std::string &source, const std::string &prefix)
{
    if(prefix.size() > source.size())
        return false;

    return std::equal(begin(prefix), end(prefix), begin(source));
}
