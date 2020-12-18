#include "impl.h"
const std::map<size_t,size_t > marks{{0, 1},
                                     {29, 1},
                                     {30, 2},
                                     {49, 2},
                                     {50, 3},
                                     {69, 3},
                                     {70, 4},
                                     {89, 4},
                                     {90, 5},
                                     {100, 5}};

size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    if(markIn100Point > 100) markIn100Point = 100;
    return marks.lower_bound(markIn100Point)->second;
}
