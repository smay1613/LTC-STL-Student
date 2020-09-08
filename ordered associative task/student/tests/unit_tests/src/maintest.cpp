#include "maintest.h"

using namespace ::testing;

TEST(Conversion, Limits)
{
    EXPECT_EQ(convertMarkTo5PointSystem(0), 1);
    EXPECT_EQ(convertMarkTo5PointSystem(30), 2);
    EXPECT_EQ(convertMarkTo5PointSystem(50), 3);
    EXPECT_EQ(convertMarkTo5PointSystem(70), 4);
    EXPECT_EQ(convertMarkTo5PointSystem(90), 5);
}

TEST(Conversion, Underlimit)
{
    EXPECT_EQ(convertMarkTo5PointSystem(0), 1);
    EXPECT_EQ(convertMarkTo5PointSystem(29), 1);
    EXPECT_EQ(convertMarkTo5PointSystem(49), 2);
    EXPECT_EQ(convertMarkTo5PointSystem(69), 3);
    EXPECT_EQ(convertMarkTo5PointSystem(89), 4);
}

TEST(Conversion, UpperLimit)
{
    EXPECT_EQ(convertMarkTo5PointSystem(1), 1);
    EXPECT_EQ(convertMarkTo5PointSystem(31), 2);
    EXPECT_EQ(convertMarkTo5PointSystem(51), 3);
    EXPECT_EQ(convertMarkTo5PointSystem(71), 4);
    EXPECT_EQ(convertMarkTo5PointSystem(91), 5);
}

TEST(Conversion, OutOfBounds)
{
    EXPECT_EQ(convertMarkTo5PointSystem(100), 5);
    EXPECT_EQ(convertMarkTo5PointSystem(200), 5);
}
