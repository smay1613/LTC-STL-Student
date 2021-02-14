#include "maintest.h"

using namespace ::testing;

TEST(Reverse, Easy)
{
    const std::string input {"the sky is blue"};
    const std::string expected {"blue is sky the"};
    EXPECT_EQ(reverseWords(input), expected);
}

TEST(Reverse, MultipleSpaces)
{
    const std::string input {"a good   example"};
    const std::string expected {"example good a"};
    EXPECT_EQ(reverseWords(input), expected);
}

TEST(Reverse, TrailingSpaces)
{
    const std::string input {"  hello world!  "};
    const std::string expected {"world! hello"};
    EXPECT_EQ(reverseWords(input), expected);
}

TEST(Reverse, Corner)
{
    const std::string input {""};
    const std::string expected {""};
    EXPECT_EQ(reverseWords(input), expected);
}

TEST(Reverse, Corner_2)
{
    const std::string input {" "};
    const std::string expected {""};
    EXPECT_EQ(reverseWords(input), expected);
}

TEST(Reverse, Corner_3)
{
    const std::string input {" . "};
    const std::string expected {"."};
    EXPECT_EQ(reverseWords(input), expected);
}
