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
    std::array<size_t, N> array = {1};
    auto op = [](const size_t& item1, const size_t& item2)
    {
        return item1 + item2;
    };
    std::adjacent_difference(std::begin(array), std::prev(std::end(array)), std::next(std::begin(array)), op);
    return array;
}
