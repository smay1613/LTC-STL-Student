#include "impl.h"

#include <algorithm>

bool startsWith(const std::string& source, const std::string& prefix)
{
    return prefix.length() <= source.length() &&
           std::equal(prefix.begin(), prefix.end(), source.begin());
}
