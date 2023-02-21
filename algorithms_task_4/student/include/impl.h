#pragma once
#include <algorithm>

/**
 * @todo Implement sliding algorithm (left/right shift of subsequence to a position)
 *
 * @param begin - begin of random-access range
 * @param last - end of random-access range
 * @param pos - new end of slided range (if right slide)
 *           or new begin of slided range (if left slide)
 *
 * @return new slided range position
 */
template <typename RandomAccessIterator>
std::pair<RandomAccessIterator, RandomAccessIterator> slide(RandomAccessIterator begin, RandomAccessIterator last, RandomAccessIterator pos){
	if (pos < begin){
		auto new_last = std::rotate(pos, begin, last);
		return std::make_pair(pos ,new_last);
	}
	else if (pos > begin) {
		auto new_first = rotate(begin, last, pos);
		return std::make_pair(new_first, pos);
	}
	return std::make_pair(begin, last);
}
