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
    const auto groupStart = std::adjacent_find(start, end, comp);

    if (groupStart == end)
    {
        return {end, end};
    }

    const auto& groupValue = *groupStart;
    auto groupEnd = std::find_if_not(groupStart,
                                     end,
                                     [&groupValue, &comp] (decltype(groupValue) value) {
                                        return comp(groupValue, value);
                                     });

    return {groupStart, groupEnd};
}
