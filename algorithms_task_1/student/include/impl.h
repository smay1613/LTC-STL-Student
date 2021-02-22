#pragma once
#include <utility>
#include <algorithm>
#include <functional>

/**
  * @todo Implement function that will find group of equal elements
  * @param start - begin of seeking range
  * @param end - end of seeking range
  * @param comparator - function to compare for equality
  * @return consecutive range
*/
template<class FI, class Comparator = std::equal_to<typename std::iterator_traits<FI>::value_type>>
std::pair<FI, FI> consecutive_group(FI start, FI end, Comparator comp = {}){
    if (start==end) {
        return {end, end};
    }

    using storingValue = typename FI::value_type;
    auto incIter = start;
    auto endOfSeq = start;
    while (incIter!=end){
        endOfSeq = std::find_if_not(incIter, end, [&start, &comp](const storingValue &value) {
            return comp(value, *start);
        });
        incIter = std::next(start);
        if (incIter!=endOfSeq){
            return {start, endOfSeq};
        }
        ++start;
    }
    return {start, endOfSeq};
}