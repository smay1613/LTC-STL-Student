#include "impl.h"

size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    std::map <size_t, size_t> converter {{29, 1}, {49, 2}, {69, 3}, {89, 4}, {90, 5}};
    auto result = converter.lower_bound(markIn100Point);
    return converter.end() != result ? result->second : converter.at(90);
}
