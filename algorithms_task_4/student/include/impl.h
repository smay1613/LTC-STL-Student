#pragma once
#include <algorithm>
#include <iterator>

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
std::pair<RandomAccessIterator, RandomAccessIterator> slide(RandomAccessIterator begin, RandomAccessIterator last, RandomAccessIterator pos)
{
    if (pos > last) {
        return { std::rotate(begin, last, pos), pos };
    } else if (pos < last) {
        return { pos, std::rotate(pos, begin, last) };
    }
    return { begin, last };
}
