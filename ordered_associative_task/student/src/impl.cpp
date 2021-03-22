#include "impl.h"

size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    std::map<size_t, size_t> markMap { {0, 1},
                                       {30, 2},
                                       {50, 3},
                                       {70, 4},
                                       {90, 5} };

    auto markRange = markMap.equal_range(markIn100Point);

    if (markRange.first == markRange.second)
    {
        --markRange.first;
    }

    return markRange.first->second;
}
