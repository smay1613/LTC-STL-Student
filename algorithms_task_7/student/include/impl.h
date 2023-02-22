#pragma once
#include <numeric>
#include <array>
#include <functional>

/**
 * @todo Implement function that will return N first fibonnaci numbers, started from 1
 * @return N first fibonacci numbers
 */

template<std::size_t N>
std::array<std::size_t, N> fibonacci(){
    std::array<std::size_t, N> fibo;
    std::fill(fibo.begin(), fibo.end(), 1);

    std::adjacent_difference(fibo.begin(), fibo.end(), fibo.begin() + 1, std::plus<std::size_t>());
    return fibo;
}
