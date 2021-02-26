#pragma once
#include <numeric>
#include <array>

/**
 * @todo Implement function that will return N first fibonnaci numbers, started from 1
 * @return N first fibonacci numbers
 */
template<size_t N>
std::array<size_t, N> fibonacci(){
    std::array<size_t, N> arr_out={1};
    std::adjacent_difference(arr_out.begin(), arr_out.end()-1, arr_out.begin()+1, [](size_t sum, size_t value){
        return sum + value;
    });
    return arr_out;
}
