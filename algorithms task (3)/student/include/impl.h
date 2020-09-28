#pragma once

#include <algorithm>

/** @todo Implement right-shifting algorithm for bidirectional ranges
 *
 *  BI - bidirectional iterator type
 *
 *  @param begin - begin of range to shift
 *  @param end - end of range to shift
 *  @param shift - how much sequence will be shifted to the right from begin to end
 *
 *  @return begin + shift
 *
 * @note behavior is undefined if shift out of bounds
 */
template<class BiIt>
BiIt shift_right_n(BiIt begin, BiIt end, typename BiIt::difference_type shift)
{
    ///Didn't get the idea for "end" parameter, as shift specifies the number of elements to shift.
    ///begin+shift - start of the destination sequence
    //return std::move_backward(begin, std::next(begin, shift), std::next(begin, shift*2));

    //source & dest ranges never overlap, so move can be used instead of move_backward.
    auto dest = std::next(begin, shift);
    std::move(begin, dest, dest);
    return dest;
}
