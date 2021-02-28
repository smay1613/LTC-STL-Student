#pragma once
#include <numeric>
#include <array>

/**
 * @todo Implement function that will return N first fibonnaci numbers, started from 1
 * @return N first fibonacci numbers
 */
template<size_t N>
std::array<size_t, N> fibonacci()
{
    std::array<size_t, N> result {1};
    std::adjacent_difference(result.begin(), std::prev(result.end()), std::next(result.begin()), std::plus<size_t>{});
    return result;
}
