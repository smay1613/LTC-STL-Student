#pragma once

#include <algorithm>
#include <iterator>
#include <type_traits>

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
void insert_to_sorted(Sequence& target, const FwIt sourceBegin, const FwIt sourceEnd)
{
    static_assert(std::is_const<typename std::remove_reference<
                      typename std::iterator_traits<FwIt>::reference>::type>::value,
                  "FwIt must point to const data");

    // Use std::upper_bound() for stable order of source values.

    std::for_each(sourceBegin, sourceEnd, [&target](const typename std::iterator_traits<FwIt>::value_type& sourceValue)
    {
        target.insert(std::upper_bound(target.begin(), target.end(), sourceValue), sourceValue);
    });
}
