#pragma once
#include <algorithm>


/**
 * @todo insert_to_sorted
 * Sequence - sequence container that support insert operation
 * FwIt - forward iterator
 *
 * @param target - target container, to which sequence will be inserted
 * @param sourceBegin - begin of the subsequence to insert, NOTE: CONST
 * @param sourceEnd - end of the subsequence to insert, NOTE: CONST
 */

/**
 * @warning IS YOUR SOLUTION STABLE?
 * WHAT IF TARGET WILL BE FILLED WITH THE DUPLICATES VALUE
 * AND WE'LL INSERT A NEW (SAME) VALUE? WILL IT BE EFFICIENT?
 */

template <typename Sequence, typename FwIt>
void insert_to_sorted(Sequence& target, const FwIt sourceBegin, const FwIt sourceEnd);
