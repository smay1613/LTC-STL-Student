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
std::pair<BiIt, BiIt> gather(BiIt begin, BiIt end, BiIt position, UnaryPredicate predicate) {
    auto invertedPredicate =
            [&predicate](typename std::iterator_traits<BiIt>::value_type val) {
                return !predicate(val);
            };

    auto partitionStart = std::partition(begin, position, invertedPredicate);
    auto partitionEnd = std::partition(position, end, predicate);
    return std::make_pair(partitionStart, partitionEnd);
}
