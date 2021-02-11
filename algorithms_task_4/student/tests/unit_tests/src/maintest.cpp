#include "maintest.h"
#include <deque>

using namespace ::testing;

TEST(SlideSame, Right)
{
    std::deque<size_t> data {1, 1, 1, 0, 0, 0, 0};

    std::deque<size_t> expected {0, 0, 0, 0, 1, 1, 1};

    constexpr size_t offset {3};
    auto endOfSlidingRange = std::next(data.begin(), offset);
    auto newSlidedRange = slide(data.begin(), endOfSlidingRange,
                                data.end());

    EXPECT_EQ(data, expected);
    EXPECT_EQ(newSlidedRange.first, std::prev(data.end(),
                                              std::distance(data.begin(), endOfSlidingRange)));
    EXPECT_EQ(newSlidedRange.second, data.end());
}

TEST(SlideSame, Left)
{
    std::deque<size_t> data {0, 0, 0, 0, 1, 1, 1};
    std::deque<size_t> expected {1, 1, 1, 0, 0, 0, 0};

    constexpr size_t offset {3};
    auto endOfSlidingRange = std::next(data.rbegin(), offset);

    auto newSlidedRange = slide(data.rbegin(), endOfSlidingRange,
                                data.rend());

    EXPECT_EQ(data, expected);
    EXPECT_EQ(newSlidedRange.first, std::prev(data.rend(),
                                              std::distance(data.rbegin(), endOfSlidingRange)));
    EXPECT_EQ(newSlidedRange.second, data.rend());
}

TEST(SlideDifferent, Right)
{
    std::deque<size_t> data {1, 2, 3, 4, 5, 6, 7};

    std::deque<size_t> expected {4, 1, 2, 3, 5, 6, 7};

    constexpr size_t offset {3};
    auto endOfSlidingRange = std::next(data.begin(), offset);
    auto newSlidedRange = slide(data.begin(), endOfSlidingRange,
                                std::next(endOfSlidingRange));

    EXPECT_EQ(data, expected);
    EXPECT_EQ(newSlidedRange.first, std::next(data.begin()));
    EXPECT_EQ(newSlidedRange.second, std::next(data.begin(), offset + 1));
}

TEST(SlideDifferent, Left)
{
    std::deque<size_t> data {5, 6, 7, 8, 1, 2, 3};
    std::deque<size_t> expected {5, 6, 7, 1, 2, 3, 8};

    constexpr size_t offset {3};
    auto endOfSlidingRange = std::next(data.rbegin(), offset);
    auto newSlidedRange = slide(data.rbegin(), endOfSlidingRange,
                                std::next(endOfSlidingRange));

    EXPECT_EQ(data, expected);
    EXPECT_EQ(newSlidedRange.first, std::next(data.rbegin()));
    EXPECT_EQ(newSlidedRange.second, std::next(data.rbegin(), offset + 1));
}
