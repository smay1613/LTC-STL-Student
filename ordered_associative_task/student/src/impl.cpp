#include "impl.h"

size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    const std::map<size_t, size_t> table { { 29, 1 }, { 49, 2 }, { 69, 3 }, { 89, 4 }, { 99, 5 } };
    auto const it = table.lower_bound(markIn100Point);
    return it != table.cend() ? it->second : 5;
}
