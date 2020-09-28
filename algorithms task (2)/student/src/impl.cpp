#include "impl.h"

bool startsWith(const std::string& source, const std::string& prefix)
{
    return std::equal(source.begin(),source.begin()+prefix.size(),prefix.begin());
}