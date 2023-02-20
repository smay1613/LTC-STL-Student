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
std::pair<FI, FI> consecutive_group(FI start, FI end, Comparator comp = {}) {
    auto first = std::adjacent_find(start, end, comp);
    if (first == end) {
        return std::make_pair(first, first);
    }
    auto second = std::find_end(first, end, first, std::next(first), comp);
    return std::make_pair(first, std::next(second));
}
