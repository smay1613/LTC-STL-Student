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
  auto first=std::adjacent_find(start,end, comp);

  auto not_comp= [&](const typename std::iterator_traits<FI>::value_type & a,const typename std::iterator_traits<FI>::value_type &  b)
  {return !comp(a,b);};
  // Since C++17 I could have used std::not_fn(comp) !!!
  
  auto second=std::adjacent_find(first,end, not_comp);
  if(second!=end){
    second=std::next(second);
  }
  return std::make_pair(first,second);

}
