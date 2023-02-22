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
     std::array<size_t, N> arr;
     std::fill(arr.begin(), arr.end(), 1);
     std::adjacent_difference(arr.begin(), arr.end(), arr.begin() + 1, std::plus<size_t>());
     return arr;
}
