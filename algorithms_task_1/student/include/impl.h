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
    using namespace std;
    using value_type = typename std::iterator_traits<FI>::value_type const &;

    auto first = adjacent_find(start, end, comp);
    auto second = find_if_not(first, end,
                              [&first, &comp](value_type current) {
                                  return comp(*first,current);
                              });

    return make_pair(first, second);
}
