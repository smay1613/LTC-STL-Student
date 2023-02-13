#pragma once
#include <map>
#include <algorithm>
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

const size_t MAX_POINTS = 100;

std::map<std::size_t, std::size_t> pointSystem{
    {30,1},
    {50,2},
    {70,3},
    {90,4},
    {101, 5}
};

std::size_t convertMarkTo5PointSystem(std::size_t markIn100Point){
    
    return pointSystem.upper_bound(std::min(markIn100Point, MAX_POINTS))->second;
}
