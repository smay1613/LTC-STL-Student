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
    auto newEnd = std::partition(position, end, predicate);

    auto lambda = [predicate](const BiIt& iter){ return !predicate(iter);

    auto newBegin = std::partition(begin, position, lambda);

    return std::pair<BiIt, BiIt>(newBegin, newEnd);
}
