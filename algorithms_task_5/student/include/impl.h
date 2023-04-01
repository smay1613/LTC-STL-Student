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
	auto first = std::partition(begin, position, 
		[&predicate](typename BiIt::value_type x) {return !predicate(x); });
	
	auto last = std::partition(position, end, predicate);
	return std::make_pair(first, last);

}
