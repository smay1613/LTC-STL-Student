#include "maintest.h"
#include <deque>

using namespace ::testing;

TEST(SlideSame, Right)
{
    std::deque<size_t> data     {0, 1, 1, 1, 0, 0, 0, 0};

    std::deque<size_t> expected {0, 0, 0, 0, 1, 1, 1, 0};

    const auto slidingRangeSize = 3;
    auto slidingRangeBegin = std::next(data.begin());
    auto slidingRangeEnd = slidingRangeBegin + slidingRangeSize;

    const auto shift = slidingRangeSize;
    auto slidingPosition = slidingRangeEnd + shift;

    auto newSlidedRange = slide(slidingRangeBegin, slidingRangeEnd, slidingPosition);

    EXPECT_EQ(data, expected);
    EXPECT_EQ(newSlidedRange.first, std::prev(slidingPosition, slidingRangeSize));
    EXPECT_EQ(newSlidedRange.second, slidingPosition);
}

TEST(SlideSame, ReverseLeft)
{
    std::deque<size_t> data     {0, 0, 0, 0, 1, 1, 1, 0};

    std::deque<size_t> expected {0, 1, 1, 1, 0, 0, 0, 0};

    const auto slidingRangeSize = 3;
    auto slidingRangeBegin = std::next(data.rbegin());
    auto slidingRangeEnd = slidingRangeBegin + slidingRangeSize;

    const auto shift = slidingRangeSize;
    auto slidingPosition = slidingRangeEnd + shift;

    auto newSlidedRange = slide(slidingRangeBegin, slidingRangeEnd, slidingPosition);

    EXPECT_EQ(data, expected);
    EXPECT_EQ(newSlidedRange.first, std::prev(slidingPosition, slidingRangeSize));
    EXPECT_EQ(newSlidedRange.second, slidingPosition);
}

TEST(SlideDifferent, Right)
{
    std::deque<size_t> data     {1, 2, 3, 4, 5, 6, 7};
    std::deque<size_t> expected {4, 1, 2, 3, 5, 6, 7};

    const auto slidingRangeSize = 3;
    auto slidingRangeBegin = data.begin();
    auto slidingRangeEnd = slidingRangeBegin + slidingRangeSize;

    const auto shift = 1;
    auto slidingPosition = slidingRangeEnd + shift;

    auto newSlidedRange = slide(slidingRangeBegin, slidingRangeEnd, slidingPosition);

    EXPECT_EQ(data, expected);
    EXPECT_EQ(newSlidedRange.first, std::prev(slidingPosition, slidingRangeSize));
    EXPECT_EQ(newSlidedRange.second, slidingPosition);
}

TEST(SlideDifferent, Left)
{
    std::deque<size_t> data       {4, 1, 2, 3, 5, 6, 7};
    std::deque<size_t> expected   {1, 2, 3, 4, 5, 6, 7};

    const auto slidingRangeSize = 3;
    auto slidingRangeBegin = std::next(data.begin());
    auto slidingRangeEnd = slidingRangeBegin + slidingRangeSize;

    const auto shift = -1;
    auto slidingPosition = std::next(slidingRangeBegin, shift);

    auto newSlidedRange = slide(slidingRangeBegin, slidingRangeEnd, slidingPosition);

    EXPECT_EQ(data, expected);
    EXPECT_EQ(newSlidedRange.first, slidingPosition);
    EXPECT_EQ(newSlidedRange.second, std::next(slidingPosition, slidingRangeSize));
}

TEST(Slide, NoSlide)
{
    std::deque<size_t> data {1, 2, 3};
    auto newSlidedRange = slide(data.begin(), data.end(), data.begin());

    EXPECT_EQ(newSlidedRange.first, data.begin());
    EXPECT_EQ(newSlidedRange.second, data.end());
}
