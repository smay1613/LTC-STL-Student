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
    if (pos == begin || pos == last) {
        return { begin, last };
    }

    bool isRightShift =  pos > last;
    if (isRightShift) {
        auto newBegin = std::rotate(begin, last, pos);
        return { newBegin, pos };
    } else {
        using rev_it = std::reverse_iterator<RandomAccessIterator>;

        auto newEnd = std::rotate(rev_it(last), rev_it(begin), rev_it(pos));
        return { pos, newEnd.base() };
    }
}
