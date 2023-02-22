#pragma once
#include <numeric>
#include <array>

/**
 * @todo Implement function that will return N first fibonnaci numbers, started from 1
 * @return N first fibonacci numbers
 */
template<size_t N>
std::array<size_t, N> fibonacci() {
    std::array<size_t, N> fibo{1};
    std::adjacent_difference(fibo.begin(), fibo.end(), std::next(fibo.begin()), std::plus<size_t>());
    return fibo;
}
