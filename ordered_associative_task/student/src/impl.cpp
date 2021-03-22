#include "impl.h"

size_t convertMarkTo5PointSystem(size_t markIn100Point) {
    auto range = marksMap.equal_range(markIn100Point);
    return (range.first==range.second?((--range.first)->second):(range.first->second));
}
