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
std::pair<BiIt, BiIt> gather(BiIt begin, BiIt end, BiIt position, UnaryPredicate predicate)
{
    using constValueTypeReference = const typename std::iterator_traits<BiIt>::value_type&;
    auto newBegin = std::partition(begin, position, [predicate](constValueTypeReference value)
    { return !predicate(value); });
    auto newEnd = std::partition(position, end, predicate);
    return {newBegin, newEnd};
}
