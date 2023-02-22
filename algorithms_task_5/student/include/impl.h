#pragma once
#include <algorithm>

template<typename argType, typename PredicateType>
struct NegatedUnaryLambda : std::unary_function<argType, bool>
{
     PredicateType predicate;

     NegatedUnaryLambda(PredicateType fn)
          : predicate(fn)
     { }

     bool operator()(argType val)
     {
          return !predicate(val);
     }
};

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
     auto first = std::stable_partition(begin, position, NegatedUnaryLambda<int, UnaryPredicate>(predicate));
     auto last = std::stable_partition(position, end, predicate);

     return {first, last};
}
