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
    const std::map <size_t, size_t> converter {{29, static_cast<size_t>(Point::ONE)},
                                               {49, static_cast<size_t>(Point::TWO)},
                                               {69, static_cast<size_t>(Point::THREE)},
                                               {89, static_cast<size_t>(Point::FOUR)},
                                               {90, static_cast<size_t>(Point::MAX_POINT)}};
    const auto result = converter.lower_bound(markIn100Point);
    return converter.end() != result ? result->second : static_cast<size_t>(Point::MAX_POINT);
}
