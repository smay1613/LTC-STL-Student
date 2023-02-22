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
    auto notpredicate = [&](const typename BiIt::value_type& value)
    {
        return !predicate(value);
    };

    return std::make_pair(
                std::partition(begin,position,notpredicate),
                std::partition(position,end,predicate)
                );

}

