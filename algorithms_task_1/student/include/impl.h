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
std::pair<FI, FI> consecutive_group(FI start, FI end, Comparator comp = {})
{
    auto firstIter = std::adjacent_find(start, end, comp);

    if (firstIter == end) {
        return std::make_pair(end, end);
    }

    using value_type = typename std::iterator_traits<FI>::value_type;
    auto secondIter = std::find_if_not(firstIter, end,
                                       [&](value_type elem){ return comp(elem, *firstIter); });
    return std::make_pair(firstIter, secondIter);
}
