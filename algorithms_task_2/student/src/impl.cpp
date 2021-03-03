#include "impl.h"

bool startsWith(const std::string& source, const std::string& prefix)
{
    auto result = std::mismatch(std::begin(source), std::end(source), std::begin(prefix));

    return result.second == std::end(prefix);
}
