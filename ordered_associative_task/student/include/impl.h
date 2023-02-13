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
int convertMarkTo5PointSystem(int markIn100Point){
    if(markIn100Point>90) markIn100Point = 90;
    std::map<int, int> m {{0, 1}, {29, 1}, {30, 2}, {49, 2}, {50, 3}, {69, 3}, {70, 4}, {89, 4}, {90, 5}};
    return m.lower_bound(markIn100Point)->second;
}
