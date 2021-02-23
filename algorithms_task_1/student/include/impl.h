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

    if (it1 == end)
    {
        return std::make_pair(end, end);
    }

    using valueType = typename std::iterator_traits<FI>::value_type;
    FI it2 = std::find_if_not( it1, end,
                               [&](const valueType &elem) { return comp(elem, *it1); });

    return std::make_pair(it1, it2);
}
