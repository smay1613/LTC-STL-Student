#include "impl.h"
#include <iostream>
size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    static const std::map<size_t, size_t> marks {
        {29, 1},
        {49, 2},
        {69, 3},
        {89, 4},
        {-1, 5},
    };

    auto it = marks.lower_bound(markIn100Point);
    return it->second;
}
