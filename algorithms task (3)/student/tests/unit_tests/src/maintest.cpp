#include "maintest.h"
using namespace ::testing;

TEST_F(Shift, HalfShift)
{
    auto out = shift_right_n(cx.begin(), std::prev(cx.end(), N / 2), N / 2);
    EXPECT_EQ(out, std::next(cx.begin(), N / 2));

    EXPECT_TRUE(std::equal(cx.begin(), out, out,
                           [](const X& lhs, const X& rhs) {return lhs.a == rhs.a; }));
}

TEST_F(Shift, SimpleMoveBy1)
{
    auto out = shift_right_n(cx.begin(), std::prev(cx.end()), 1);
    EXPECT_EQ(out, std::next(cx.begin()));

    EXPECT_TRUE(std::all_of(cx.begin(), out,
                            [] (const X& x) { return x.moved_from;}));

    EXPECT_TRUE(std::all_of(out, cx.end(),
                            [] (const X& x) { return !x.moved_from;}));
}

