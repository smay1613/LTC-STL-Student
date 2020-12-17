#include "impl.h"

size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    const std::map<size_t, size_t> marksLUT{{29, 1}, {49, 2}, {69, 3}, {89, 4}, {100, 5}};

    const auto it = marksLUT.lower_bound(markIn100Point);

    return it != marksLUT.cend() ? it->second
                                 : std::prev(it)->second;
}
