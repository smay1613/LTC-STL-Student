#include "impl.h"

size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    enum Point
    {
        ONE = 1,
        TWO,
        THREE,
        FOUR,
        MAX_POINT
    };
    const std::map <size_t, size_t> converter {{29, Point::ONE}, {49, Point::TWO}, {69, Point::THREE}, {89, Point::FOUR}, {90, Point::MAX_POINT}};
    const auto result = converter.lower_bound(markIn100Point);
    return converter.end() != result ? result->second : Point::MAX_POINT;
}
