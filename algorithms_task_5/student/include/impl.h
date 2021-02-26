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
    using ValueType = typename BiIt::value_type;
    auto rangeBegin = std::partition(begin,
                                   position,
                                   [predicate] (const ValueType& value) {
        return !predicate(value);
    });

    auto rangeEnd = std::partition(position, end, predicate);

    return {rangeBegin, rangeEnd};
}
