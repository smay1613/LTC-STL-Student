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
size_t convertMarkTo5PointSystem(size_t markIn100Point){
    std::map<size_t,size_t> ranges={{29,1},{49,2},{69,3},{89,4}};
     const auto it=ranges.lower_bound(markIn100Point);
     if(ranges.cend()==it){
         return 5;
     }
     return it->second;
}
