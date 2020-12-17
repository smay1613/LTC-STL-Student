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
    std::map<size_t, size_t> conv = { {0, 1},
                                 {29, 1},
                                 {30, 2},
                                 {49, 2},
                                 {50, 3},
                                 {69, 3},
                                 {70, 4},
                                 {89, 4},
                                 {90, 5}
                                };

    auto lower_ = conv.lower_bound(markIn100Point);

    if(lower_ != conv.end()) {
        return lower_->second;
    } else {
        return 5;
    }
}
