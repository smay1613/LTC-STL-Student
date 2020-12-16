#include "impl.h"

size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    static std::map<size_t, size_t> marks {{30, 1}, {50, 2}, {70, 3}, {90, 4}};

    for (auto markPair: marks) {
        if (markIn100Point < markPair.first) {
            return markPair.second;
        }
    }

    return 5; // + out of bound cases
}
