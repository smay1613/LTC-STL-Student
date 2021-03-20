#include "maintest.h"
#include <utility>
#include <random>
#include <algorithm>

using namespace ::testing;

TEST(Anagrams, PositiveWithDuplications)
{
    playlist tracklist1 {10, {"1"}};
    tracklist1.insert(tracklist1.end(), 10, {"4"});
    tracklist1.insert(tracklist1.end(), 10, {"1"});
    tracklist1.insert(tracklist1.end(), 10, {"2"});

    playlist tracklist2 {tracklist1};
    std::shuffle(tracklist2.begin(), tracklist2.end(),
                 std::default_random_engine{});

    EXPECT_TRUE(is_same_content(tracklist1, tracklist2));
    EXPECT_TRUE(is_same_content(tracklist2, tracklist1));
}

TEST(Anagrams, PositiveNoDuplications)
{
    std::vector<std::string> data {{"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"a"}, {"b"}};

    auto fill = [&] (playlist& tracklist) {
        std::transform(data.begin(), data.end(), std::back_inserter(tracklist),
            [](const std::string& name) {
                return Song {name};
            });
    };

    playlist tracklist1;
    fill(tracklist1);

    while(std::next_permutation(data.begin(), data.end())) {
        playlist tracklist2;
        fill(tracklist2);
        EXPECT_TRUE(is_same_content(tracklist1, tracklist2));
        EXPECT_TRUE(is_same_content(tracklist2, tracklist1));
    }

}

TEST(Anagrams, NegativeNewElements)
{
    playlist tracklist1 {{"a"}, {"b"}, {"c"}, {"c"}};
    playlist tracklist2 {{"a"}, {"b"}, {"c"}, {"d"}};
    EXPECT_FALSE(is_same_content(tracklist1, tracklist2));
    EXPECT_FALSE(is_same_content(tracklist2, tracklist1));
}

TEST(Anagrams, NegativeMoreElements)
{
    playlist tracklist1 {{"a"}, {"b"}, {"c"}};
    playlist tracklist2 {{"a"}, {"b"}, {"c"}, {"b"}};
    EXPECT_FALSE(is_same_content(tracklist1, tracklist2));
    EXPECT_FALSE(is_same_content(tracklist2, tracklist1));
}
