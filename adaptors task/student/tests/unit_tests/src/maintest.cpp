#include "maintest.h"

using namespace ::testing;

TEST(Balanced, Easy)
{
    EXPECT_TRUE(isValid("[]"));
    EXPECT_TRUE(isValid("{}"));
    EXPECT_TRUE(isValid("()"));
}

TEST(Balanced, Subexpressions_Positive)
{
    EXPECT_TRUE(isValid("[{()}]"));
    EXPECT_TRUE(isValid("[(){}]"));
    EXPECT_TRUE(isValid("({}[()])"));
}

TEST(Balanced, OneSymbol)
{
    EXPECT_FALSE(isValid("["));
    EXPECT_FALSE(isValid("]"));
    EXPECT_FALSE(isValid("("));
    EXPECT_FALSE(isValid(")"));
    EXPECT_FALSE(isValid("{"));
    EXPECT_FALSE(isValid("}"));
}

TEST(Balanced, NotClosedOrOpened)
{
    EXPECT_FALSE(isValid("[["));
    EXPECT_FALSE(isValid("]]"));
    EXPECT_FALSE(isValid("(["));
    EXPECT_FALSE(isValid("(){"));
    EXPECT_FALSE(isValid(")[]("));
}

TEST(Balanced, AntiCounter)
{
    EXPECT_FALSE(isValid("(]"));
    EXPECT_FALSE(isValid("(}"));
    EXPECT_FALSE(isValid("(()][)"));

}

TEST(Balanced, Empty)
{
    EXPECT_TRUE(isValid(""));
}

TEST(Balanced, Simple)
{
    EXPECT_TRUE(isValid("{}"));
    EXPECT_TRUE(isValid("()"));
    EXPECT_TRUE(isValid("[]"));
}

TEST(Balanced, AdditionalData)
{
    EXPECT_TRUE(isValid("{a}"));
    EXPECT_TRUE(isValid("(b)"));
    EXPECT_TRUE(isValid("[c]"));
    EXPECT_TRUE(isValid("{a(b)c}"));
    EXPECT_FALSE(isValid("(a[b)c]a"));
    EXPECT_TRUE(isValid("aa"));
}

TEST(Balanced, Subexpression_Negative)
{
    EXPECT_FALSE(isValid("([)]"));
    EXPECT_FALSE(isValid("[{({)}]"));
}
