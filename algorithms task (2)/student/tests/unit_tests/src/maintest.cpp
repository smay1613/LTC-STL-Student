#include "maintest.h"

using namespace ::testing;

TEST(PrefixCheck, Empty)
{
    EXPECT_TRUE(startsWith("", ""));
}

TEST(PrefixCheck, EmptyPrefix)
{
    EXPECT_TRUE(startsWith("hello", ""));
}

TEST(PrefixCheck, Equal)
{
    EXPECT_TRUE(startsWith("hello", "hello"));
}

TEST(PrefixCheck, Bigger)
{
    EXPECT_FALSE(startsWith("hello", "helloworld"));
}

TEST(PrefixCheck, Smaller)
{
    EXPECT_TRUE(startsWith("hello", "hel"));
}

TEST(PrefixCheck, NonPrefix)
{
    EXPECT_FALSE(startsWith("hello", "world"));
}

TEST(PrefixCheck, NotFullPrefix)
{
    EXPECT_FALSE(startsWith("hello", "her"));
}
