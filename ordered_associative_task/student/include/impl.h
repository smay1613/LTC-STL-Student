#pragma once
#include <map>

/**
 * @todo Implement function for conversion from 100 point system to 5 point system
 *
 * @example
 * 0-29 – 1;
 * 30-49 – 2;
 * 50-69 – 3;
 * 70-89 – 4;
 * 90+ - 5
 *
 * @param markIn100Point - mark in 100 point system, could be everything.
 *
 * @return 1-5
 */
size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    const size_t DEFAULT_VALID_VALUE = 5;

    std::map<size_t, size_t> conv = {{0, 1},
                                     {30, 2},
                                     {50, 3},
                                     {70, 4},
                                     {90, 5}
                                    };

    auto upper_ = conv.upper_bound(markIn100Point);

    size_t result;

    if(upper_ == conv.begin()) {
        result = DEFAULT_VALID_VALUE;
    } else if(upper_ != conv.end()) {
        result = --upper_->second;
    } else {
        result = DEFAULT_VALID_VALUE;
    }

    return result;
}
