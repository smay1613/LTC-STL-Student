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
    using namespace std;
    using value_type = typename std::iterator_traits<BiIt>::value_type const &;

    auto leftPartition = partition(begin,position,
                                   [&predicate](value_type value){return !predicate(value);});

    auto rightPartition = partition(position, end, predicate);

    return {leftPartition, rightPartition};
}
