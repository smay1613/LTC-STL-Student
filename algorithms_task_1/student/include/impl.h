#pragma once
#include <utility>
#include <algorithm>
#include <functional>
#include <iostream>

/**
  * @todo Implement function that will find group of equal elements
  * @param start - begin of seeking range
  * @param end - end of seeking range
  * @param comparator - function to compare for equality
  * @return consecutive range
*/
template<class FI, class T = typename std::iterator_traits<FI>::value_type, class Comparator = std::equal_to<T>>
std::pair<FI, FI> consecutive_group(FI start, FI end, Comparator comp = {})
{
  auto first = std::adjacent_find(start, end, comp);
  
  if (first == end)
    return {end, end};

  auto val = *first;

  auto last = std::find_if_not(first, end, 
    [&](T element)
    {
      return val == element;
    }
  );

  return {first, last};
}
