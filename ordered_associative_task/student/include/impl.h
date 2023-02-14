#pragma once
#include <map>

/**
 * @todo Implement function for conversion from 100 point system to 5 point system
 *
 * @example
 * 0-29 – 1;
 * 30-49 – 2;
 * 50-69 – 3;
 * 70-89 – 4;
 * 90+ - 5
 *
 * @param markIn100Point - mark in 100 point system, could be everything.
 *
 * @return 1-5
 */
std::size_t convertMarkTo5PointSystem(std::size_t markIn100Point) {
    const std::size_t MAX100POINT = 100;
    const std::size_t MAX5POINT = 5;
    std::map<std::size_t, std::size_t> map {
        {29, 1},
        {49, 2},
        {69, 3},
        {89, 4},
        {100, 5}
    };

    if (markIn100Point > MAX100POINT) {
        return MAX5POINT;
    }

    auto it = map.lower_bound(markIn100Point);
    return (*it).second;
}
