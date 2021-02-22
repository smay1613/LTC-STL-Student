#include "impl.h"
#include <algorithm>

bool startsWith(const std::string& source, const std::string& prefix)
{
    /*
     * substr
     * strncmp
     * rfind
     * search
     */
    if (prefix.size() > source.size()) {
        return false;
    }

    return std::equal(prefix.cbegin(), prefix.cend(), source.cbegin());
}
