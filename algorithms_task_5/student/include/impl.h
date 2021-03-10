#pragma once
#include <algorithm>
#include <functional>

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
    std::function<bool(const typename std::iterator_traits<BiIt>::value_type&)> pred = predicate;
    auto pivot = std::partition(begin, end, std::not1(pred));
    auto newBegin = pivot;
    auto newEnd = end;

    if (std::distance(begin, position) < std::distance(begin, pivot))
    {
        newBegin = position;
        newEnd = std::rotate(position, pivot, end);
    }

    return std::make_pair(newBegin, newEnd);
}
