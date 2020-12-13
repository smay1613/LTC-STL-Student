#pragma once
#include <list>
#include <iterator>
#include <algorithm>

/** @todo implement effective list rotation algorithm
 *
 * T - value type
 * BI - iterator type
 *
 * @param list - container, for which rotation will be done
 * @param begin - begin of sequence that will be rotated
 * @param end - end of a sequence that will be rotated
 * @param new_begin - new position of rotated sequence
 *
 * @note See https://en.cppreference.com/w/cpp/algorithm/rotate
 */
template<class T, class BI>
void rotate(std::list<T>& list, BI begin, BI new_begin, BI end)
{
    std::reverse(begin, new_begin);
    std::reverse(new_begin, end);

    while(begin != new_begin && new_begin != end)
        std::iter_swap(begin++, --end);

    if   (begin == new_begin) std::reverse(new_begin, end);
    else                      std::reverse(begin, new_begin);
}
