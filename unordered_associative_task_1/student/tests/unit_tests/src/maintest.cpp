#include "maintest.h"
#include <utility>

using namespace ::testing;

TEST(Anagrams, PositiveDifferent)
{
    std::string testString {"12356abс"};
    std::string original {testString};
    while (std::next_permutation(testString.begin(), testString.end()))
    {
        EXPECT_TRUE(is_anagram(testString, original));
    }
}

TEST(Anagrams, PositiveSame)
{
    std::string testString {10, '1'};
    testString.insert(testString.end(), 10, '4');
    testString.insert(testString.end(), 10, '1');
    testString.insert(testString.end(), 10, '2');

    std::string original {testString};
    EXPECT_TRUE(is_anagram(testString, original));
}

TEST(Anagrams, NegativeDifferent)
{
    std::string testString {"12bс"};
    std::string modified {testString};
    modified.front() = 'k';
    while (std::next_permutation(testString.begin(), testString.end()))
    {
        EXPECT_FALSE(is_anagram(testString, modified));
    }
}

TEST(Anagrams, NegativeSame)
{
    std::string testString {10, '2'};
    std::string modified {testString};
    modified.push_back('2');

    while (std::next_permutation(testString.begin(), testString.end()))
    {
        EXPECT_FALSE(is_anagram(testString, modified));
    }
}
