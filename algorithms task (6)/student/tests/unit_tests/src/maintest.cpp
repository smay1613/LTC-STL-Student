#include "maintest.h"
#include <list>
#include <deque>

using namespace ::testing;

TEST(InsertionToSorted, Empty)
{
    std::list<size_t> data {1, 2, 4, 8, 16};
    const std::list<size_t> unsorted {};

    std::list<size_t> expected {data};

    insert_to_sorted(data, unsorted.begin(), unsorted.end());
    EXPECT_EQ(data, expected);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(InsertionToSorted, OneElement)
{
    std::list<size_t> data {1, 4, 8, 16};
    const std::list<size_t> unsorted {2};

    std::list<size_t> expected {1, 2, 4, 8, 16};

    insert_to_sorted(data, unsorted.begin(), unsorted.end());

    EXPECT_EQ(data, expected);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(InsertionToSorted, Reversed)
{
    std::list<size_t> data {1, 2, 4, 8, 16};
    std::list<size_t> unsorted;
    std::reverse_copy(data.begin(), data.end(), std::back_inserter(unsorted));

    std::list<size_t> expected {1, 1, 2, 2, 4, 4, 8, 8, 16, 16};

    const auto& unsortedRef = unsorted;
    insert_to_sorted(data, unsortedRef.begin(), unsortedRef.end());

    EXPECT_EQ(data, expected);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(InsertionToSorted, RandomAccess)
{
    std::deque<size_t> data {1, 2, 4, 8, 16};
    std::deque<size_t> unsorted;
    std::reverse_copy(data.begin(), data.end(), std::back_inserter(unsorted));

    std::deque<size_t> expected {1, 1, 2, 2, 4, 4, 8, 8, 16, 16};

    const auto& unsortedRef = unsorted;
    insert_to_sorted(data, unsortedRef.begin(), unsortedRef.end());

    EXPECT_EQ(data, expected);
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}
