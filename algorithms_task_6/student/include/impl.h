#pragma once
#include <algorithm>
#include <list>


/**
 * @todo insert_to_sorted
 * Sequence - sequence container that support insert operation
 * FwIt - forward iterator
 *
 * @param target - target container, to which sequence will be inserted
 * @param sourceBegin - begin of the subsequence to insert, NOTE: CONST
 * @param sourceEnd - end of the subsequence to insert, NOTE: CONST
 */

template<typename Cont>
void sortContainer(Cont& target) {
	std::sort(target.begin(), target.end());
}
template<typename T>
void sortContainer(std::list<T>& target) {
	target.sort();
}


template <typename Sequence, typename FwIt>
void insert_to_sorted(Sequence& target, const FwIt sourceBegin, const FwIt sourceEnd)
{
    static_assert(std::is_const<typename std::remove_reference<
                          typename std::iterator_traits<FwIt>::reference>::type>::value,
                      "FwIt must point to const data");
	std::copy(sourceBegin, sourceEnd, std::back_inserter(target));
	sortContainer(target);
}
