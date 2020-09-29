#pragma once

#include <algorithm>
#include <utility>

/**
 * @todo Implement sliding algorithm (left/right shift of subsequence to a position)
 *
 * @param begin - begin of random-access range
 * @param last - end of random-access range
 * @param pos - new begin of slided range to the left, or new end of slided range to the right.
 *
 * @return new slided range position
 */
template <typename RandomAccessIterator>
std::pair<RandomAccessIterator, RandomAccessIterator> slide(RandomAccessIterator begin, RandomAccessIterator last, RandomAccessIterator pos)
{
    if (pos < begin) // left shift
    {
        return {pos, std::rotate(pos, begin, last)};
    }
    if (last < pos) // right shift
    {
        return {std::rotate(begin, last, pos), pos};
    }
    return {begin, last};
}
