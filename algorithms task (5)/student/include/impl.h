#pragma once
#include <algorithm>
#include <functional>
#include <iostream>

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
    using Type = decltype(*begin);
    auto not_predicate = [predicate](Type& x) { return !predicate(x); };
    auto first = std::stable_partition(begin, position, not_predicate);
    auto last = std::stable_partition(position, end, predicate);
    return std::make_pair(first, last);
}
