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
    auto it_start = std::adjacent_find(start, end, comp);
    bool equalsNotFound = it_start == end;
    if (equalsNotFound) {
        return std::make_pair(end, end);
    }
    auto value = *it_start;
    auto it_end = find_if_not(it_start, end, [&value](const typename std::iterator_traits<FI>::value_type& current_value) {return current_value == value;});
    return std::make_pair(it_start, it_end);
}
