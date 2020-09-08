#include "maintest.h"
#include <array>

using namespace ::testing;

TEST(Fibonacci, Predefined)
{
    auto fibonacciResult = fibonacci<10>();
    EXPECT_EQ(fibonacciResult, (std::array<size_t, 10> {1, 1, 2, 3, 5, 8, 13, 21, 34, 55}));
}

TEST(Fibonacci, Big)
{
    auto fibonacciResult = fibonacci<30>();
    for (size_t i = 1; i < fibonacciResult.size() - 1; ++i)
    {
        EXPECT_EQ(fibonacciResult[i + 1], fibonacciResult[i - 1] + fibonacciResult[i]);
    }
}
