#pragma once

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
BiIt shift_right_n(BiIt begin, BiIt end, typename BiIt::difference_type shift);
