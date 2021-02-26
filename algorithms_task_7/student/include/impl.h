#pragma once
#include <numeric>
#include <array>

/**
 * @todo Implement function that will return N first fibonnaci numbers, started from 1
 * @return N first fibonacci numbers
 */
template<size_t N>
std::array<size_t, N> fibonacci() {
    std::array<size_t, N> result = {1};
    std::adjacent_difference(std::begin(result), std::prev(std::end(result)),
                             std::next(std::begin(result)), std::plus<size_t>());

    return result;
};
