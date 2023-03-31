#include "impl.h"


size_t convertMarkTo5PointSystem(size_t markIn100Point) {
    
    std::map<size_t, size_t> mapConverter = {
        {0,1},
        {30,2},
        {50,3},
        {70,4},
        {90,5}
        };

    auto result = mapConverter.lower_bound(markIn100Point);

    if (result == mapConverter.end() || result->first > markIn100Point) {
        result--;
    }

    return result->second;
}