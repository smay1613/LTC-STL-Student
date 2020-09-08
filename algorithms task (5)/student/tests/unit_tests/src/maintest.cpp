#include "maintest.h"
#include <list>
#include <numeric>

using namespace ::testing;

TEST(Gather, Empty)
{
    std::list<size_t> empty;
    auto result = gather(empty.begin(), empty.end(), empty.begin(), [] (const size_t) {return true;});
    EXPECT_EQ(result, std::make_pair(empty.end(), empty.end()));
}

bool is_even (int i) { return i % 2 == 0; }
bool is_ten  (int i) { return i == 10; }

template <typename Iterator, typename Predicate>
void test_iterators (Iterator first, Iterator last, Predicate comp, std::size_t offset)
{
    //  Create the pivot point
    Iterator off = std::next(first, offset);
    //  Gather the elements
    std::pair<Iterator, Iterator> res = gather (first, last, off, comp);

    //  We should now have three sequences, any of which may be empty:
    //      * [begin .. result.first)         - items that do not satisfy the predicate
    //      * [result.first .. result.second) - items that do satisfy the predicate
    //      * [result.second .. end)          - items that do not satisfy the predicate
    EXPECT_TRUE(std::none_of(first, res.first, comp));
    EXPECT_TRUE(std::all_of(res.first, res.second, comp));
    EXPECT_TRUE(std::none_of(res.second, last, comp));
}

TEST_F(GatherSequence, AtBeginning)
{
    test_iterators (container.begin(), container.end(), less_than<int> {5}, 0);
}

TEST_F(GatherSequence, AtMiddle)
{
    test_iterators (container.begin(), container.end(), less_than<int>(10),  5);
}

TEST_F(GatherSequence, AtEnd)
{
    test_iterators (container.begin(), container.end(), less_than<int>(10), container.size () - 1);       // at end
}

TEST_F(GatherSequence, Predicate)
{
    test_iterators (container.begin (), container.end(), is_even, 0);
    test_iterators (container.begin (), container.end(), is_even, 5);
    test_iterators (container.begin (), container.end(), is_even, container.size () - 1);
}

TEST_F(GatherSequence, OnlyOne)
{
    test_iterators (container.begin(), container.end(), is_ten, 0);
    test_iterators (container.begin(), container.end(), is_ten, 5);
    test_iterators (container.begin(), container.end(), is_ten, container.size () - 1);
}

TEST_F(GatherSequence, Every)
{
    test_iterators (container.begin(), container.end(), less_than<int>(99),  0);
    test_iterators (container.begin(), container.end(), less_than<int>(99),  5);
    test_iterators (container.begin(), container.end(), less_than<int>(99), container.size () - 1);
}

TEST_F(GatherSequence, Nothing)
{
    test_iterators (container.begin(), container.end(), less_than<int>(0),  0);
    test_iterators (container.begin(), container.end(), less_than<int>(0),  5);
    test_iterators (container.begin(), container.end(), less_than<int>(0), container.size () - 1);
}

TEST_F(GatherSequenceOfDuplicates, Every)
{
    test_iterators (container.begin(), container.end(), is_ten, 0);
    test_iterators (container.begin(), container.end(), is_ten, 5);
    test_iterators (container.begin(), container.end(), is_ten, container.size () - 1);
}

TEST_F(GatherSequenceOfDuplicates, Nothing)
{
    test_iterators (container.begin(), container.end(), less_than<int>(5),  0);
    test_iterators (container.begin(), container.end(), less_than<int>(5),  5);
    test_iterators (container.begin(), container.end(), less_than<int>(5), container.size () - 1);
}
