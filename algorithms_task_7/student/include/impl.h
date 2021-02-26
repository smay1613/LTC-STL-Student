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
    //adjacent_difference
    std::array<size_t, N> arr{1};
    std::adjacent_difference(arr.begin(), std::prev(arr.end()), std::next(arr.begin()), std::plus<size_t>());
    return arr;

    // partial_sum
//    std::array<size_t, N> arr{2, 1};
//    std::partial_sum(arr.begin(), std::prev(arr.end(), 2), std::next(arr.begin(), 2));
//    arr[0] = 1;
//    return arr;
}
