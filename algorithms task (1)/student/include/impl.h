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
    auto subStart = std::adjacent_find(start, end, comp);
    auto compareWithSubStart = [&subStart](typename std::iterator_traits<FI>::value_type value) -> bool
    {
        return value == *subStart;
    };
    auto subEnd = std::find_if_not(subStart, end, compareWithSubStart);
    return std::make_pair(subStart, subEnd);
}
