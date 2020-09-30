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
std::pair<RandomAccessIterator, RandomAccessIterator>
slide(RandomAccessIterator begin, RandomAccessIterator last, RandomAccessIterator pos)
{
    auto first = std::rotate(begin, last, pos);
    return std::make_pair(first, std::next(first, std::distance(begin, last)));
}
