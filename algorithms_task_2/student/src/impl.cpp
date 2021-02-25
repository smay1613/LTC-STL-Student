#include "impl.h"



bool startsWith(const std::string& source, const std::string& prefix) {
    if (prefix.size() > source.size())
        return false;

    return std::equal(prefix.cbegin(), prefix.cend(), source.cbegin());
}
