#include "maintest.h"

using namespace ::testing;

TEST(Rotate, LeftSimple)
{
    std::list<size_t> data {0, 1, 2, 3, 4, 5};
    // 0 is moved to the end
    rotate(data, data.begin(), std::next(data.begin()), data.end());

    std::list<size_t> expected {1, 2, 3, 4, 5, 0};
    EXPECT_EQ(data, expected);
}

TEST(Rotate, RightSimple)
{
    std::list<size_t> data {0, 1, 2, 3, 4, 5};
    // 5 moved to the begin
    rotate(data, data.begin(), std::prev(data.end()), data.end());

    std::list<size_t> expected {5, 0, 1, 2, 3, 4};
    EXPECT_EQ(data, expected);
}

TEST(Rotate, 3Left)
{
    std::list<size_t> data {0, 1, 2, 3, 4, 5};
    // 0 - 2 are moved to the end
    rotate(data, data.begin(), std::next(data.begin(), 3), data.end());

    std::list<size_t> expected {3, 4, 5, 0, 1, 2};
    EXPECT_EQ(data, expected);
}

TEST(Rotate, 2Left)
{
    std::list<size_t> data {0, 1, 2, 3, 4, 5};
    // 0 - 1 are moved to the end
    rotate(data, data.begin(), std::next(data.begin(), 2), data.end());

    std::list<size_t> expected {2, 3, 4, 5, 0, 1};
    EXPECT_EQ(data, expected);
}

TEST(Rotate, 2Right)
{
    std::list<size_t> data {0, 1, 2, 3, 4, 5};
    // 4-5 moved to the begin
    rotate(data, data.begin(), std::prev(data.end(), 2), data.end());

    std::list<size_t> expected {4, 5, 0, 1, 2, 3};
    EXPECT_EQ(data, expected);
}
