#include "impl.h"

size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    const std::map<size_t, size_t> scale {{29, 1}, {49, 2}, {69, 3}, {89, 4}};
    size_t ret = 5;
    auto it = scale.lower_bound(markIn100Point);
    if(it != scale.end())
    {
        ret = it->second;
    }
    return ret;
}
