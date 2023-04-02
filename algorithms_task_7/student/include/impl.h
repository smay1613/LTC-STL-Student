#pragma once
#include <numeric>
#include <array>
#include <functional>

/**
 * @todo Implement function that will return N first fibonnaci numbers, started from 1
 * @return N first fibonacci numbers
 */
template<std::size_t N>
std::array<std::size_t, N> fibonacci() {
    std::array<std::size_t, N> fib;
    std::fill(fib.begin(), fib.end(), 1);

    std::adjacent_difference(fib.begin(), fib.end(), fib.begin() + 1, std::plus<std::size_t>());
    return fib;
}
