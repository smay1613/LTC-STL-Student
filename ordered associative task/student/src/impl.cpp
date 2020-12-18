#include "impl.h"

size_t convertMarkTo5PointSystem(size_t markIn100Point) {
    std::map<size_t, int> markMap;
    markMap.emplace(29, 1);
    markMap.emplace(49, 2);
    markMap.emplace(69, 3);
    markMap.emplace(89, 4);

    auto result = markMap.lower_bound(markIn100Point);

    return result != markMap.end() ? result->second : 5;
}
