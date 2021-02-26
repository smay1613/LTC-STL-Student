#pragma once
#include <numeric>
#include <array>

/**
 * @todo Implement function that will return N first fibonnaci numbers, started from 1
 * @return N first fibonacci numbers
 */
template<size_t N>
std::array<size_t, N> fibonacci() {
    using namespace std;
    array<size_t, N> fibonacciNumbers {1};
    adjacent_difference(begin(fibonacciNumbers), prev(end(fibonacciNumbers)), next(begin(fibonacciNumbers)),
                        plus<size_t> {});
    return fibonacciNumbers;
}
