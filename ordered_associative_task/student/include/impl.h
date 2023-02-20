#pragma once
#include <map>
#include <stddef.h>

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
size_t convertMarkTo5PointSystem(size_t markIn100Point){
    std::map<size_t, size_t> gradeMap = {
                {0, 1},
                {30, 2},
                {50, 3},
                {70, 4},
                {90, 5}
            };

    for (auto it = gradeMap.rbegin(); it != gradeMap.rend(); ++it) {
        if (markIn100Point >= it->first) {
            return it->second;
        }
    }

    return 0;
}
