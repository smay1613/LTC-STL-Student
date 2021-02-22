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
    FI it1 = std::adjacent_find(start, end, comp);
    FI it2 = (it1 != end) ? std::find_if_not( std::next(it1), end, [&](typename std::iterator_traits<FI>::value_type elem){return comp(elem, *it1);} ) : end;
    return std::make_pair(it1, it2);
}
