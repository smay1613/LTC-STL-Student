#pragma once

#include <algorithm>
#include <iterator>

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
    const auto notPredicate = [predicate](const typename std::iterator_traits<BiIt>::value_type& value)
    {
        return !predicate(value);
    };

    if (position == end)
    {
        return { std::partition(begin, end, notPredicate), end };
    }

    const auto leftPartitionEnd = std::next(position);
    const auto partitionBegin = std::partition(begin, leftPartitionEnd, notPredicate);
    const auto partitionEnd = std::partition(position, end, predicate);

    return { partitionBegin != leftPartitionEnd ? partitionBegin : position, partitionEnd };
}
