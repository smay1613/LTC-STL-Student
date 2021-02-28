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

template <typename Sequence, typename FwIt>
void insert_to_sorted(Sequence& target, const FwIt sourceBegin, const FwIt sourceEnd)
{
    static_assert(std::is_const<typename std::remove_reference<
                          typename std::iterator_traits<FwIt>::reference>::type>::value,
                      "FwIt must point to const data");

    using value_type = typename std::iterator_traits<FwIt>::value_type;

    std::for_each(sourceBegin, sourceEnd, [&] (const value_type& value) {
        auto targetPos = std::lower_bound(target.begin(), target.end(), value);
        target.insert(targetPos, value);
    });
}
