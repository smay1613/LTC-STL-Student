#pragma once
#include <map>

std::map<size_t, size_t> gradePoints = {
    {29, 1},
    {49, 2},
    {69, 3},
    {89, 4},
    {100, 5}
};

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
size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    const size_t MAX_POINTS = 100;
    auto it = gradePoints.lower_bound(std::min<size_t>(markIn100Point, MAX_POINTS));

    return it->second;
}
