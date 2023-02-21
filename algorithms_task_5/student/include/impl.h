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
std::pair<BiIt, BiIt> gather(BiIt begin, BiIt end, BiIt position, UnaryPredicate predicate){

    auto notPredicate = [&] (const typename BiIt::value_type& value) {return !predicate(value);};
    
    auto first = std::partition(begin, position, notPredicate);

    auto last = std::partition(position, end, predicate);
    return {first, last};
}
