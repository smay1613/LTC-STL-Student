#pragma once
#include <map>

using namespace std;

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
    map<pair<size_t, size_t>, size_t> GradeIntervals = {{{0, 29},1},{{30, 49},2},{{50, 69},3},{{70, 89},4},{{90, 100},5}};
    for (const auto it : GradeIntervals){
        if (markIn100Point >= it.first.first || markIn100Point <= it.first.second){
            return it.second;
        }
    }
}
        
