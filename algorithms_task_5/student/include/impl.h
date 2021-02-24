#pragma once
#include <algorithm>

/**
 * @todo Implement function that will bring all values satisfying predicate to specified position
 * @param begin - begin of seeking range
 * @param end - end of seeking range
 * @param position - position to bring
 * @param predicate - unary predicate
 * @return gathered range
 */
template <typename BiIt, typename UnaryPredicate>
std::pair<BiIt, BiIt> gather(BiIt begin, BiIt end, BiIt position, UnaryPredicate predicate){
    const auto &_end= std::partition(position,end,predicate);
    const auto &_beg =std::partition(begin,position,
                                     [&](typename std::iterator_traits<BiIt>::value_type val){return !predicate(val);});
    return std::make_pair(_beg,_end);
}
