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
    BiIt gatheredBegin = std::partition(begin, position,
                                        [&] (const typename BiIt::value_type& item) {return !predicate(item);} );

    BiIt gatheredEnd = std::partition(position, end, predicate);
    return std::make_pair(gatheredBegin, gatheredEnd);
}
