#include "impl.h"

bool startsWith(const std::string& source, const std::string& prefix)
{
    return std::equal(prefix.begin(), prefix.end(), source.begin());
}