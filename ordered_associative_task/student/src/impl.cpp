#include "impl.h"

size_t convertMarkTo5PointSystem(size_t markIn100Point) {

    const std::map<size_t, size_t> mapOfMarks { {0, 1}, {30, 2}, {50, 3}, {70, 4}, {90, 5} };

    auto it = mapOfMarks.upper_bound(markIn100Point);

    size_t res = it == mapOfMarks.end() ? 5 : (--it)->second;
    return res;
}
