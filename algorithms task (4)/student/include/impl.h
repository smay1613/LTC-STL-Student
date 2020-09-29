#pragma once
#include <algorithm>

/**
 * @todo Implement sliding algorithm (left/right shift of subsequence to a position)
 *
 * @param begin - begin of random-access range
 * @param last - end of random-access range
 * @param pos - new begin of slided range
 *
 * @return new slided range position
 */
template <typename RandomAccessIterator>
std::pair<RandomAccessIterator, RandomAccessIterator> slide(RandomAccessIterator begin, RandomAccessIterator last, RandomAccessIterator pos)
{
    auto newBegin = std::rotate(begin, last, pos);
    auto slideRangeDistance = std::distance(begin, last);
    auto newLast = std::next(newBegin, slideRangeDistance);
    return std::make_pair(newBegin, newLast);
}
