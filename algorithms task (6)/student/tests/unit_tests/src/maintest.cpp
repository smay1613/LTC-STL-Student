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

template <class Container>
struct counting_iterator
{
    using iterator_category = typename Container::iterator::iterator_category;
    using value_type        = typename Container::value_type;
    using difference_type   = typename Container::difference_type;
    using pointer           = typename Container::pointer;
    using reference         = typename Container::reference;

    counting_iterator(typename Container::iterator container_it, int& inc_counter)
        : container_it_(std::move(container_it)), inc_counter_(inc_counter) {}

    decltype(auto) operator*() { return *container_it_; }

    decltype(auto) operator=(const counting_iterator& rhs)       { return container_it_ = rhs.container_it_; }
    decltype(auto) operator-(const counting_iterator& rhs) const { return container_it_ - rhs.container_it_; }

    decltype(auto) operator==(const counting_iterator& rhs) const { return container_it_ == rhs.container_it_; }
    decltype(auto) operator!=(const counting_iterator& rhs) const { return !(*this == rhs); }

    decltype(auto) operator++()
    {
        ++inc_counter_;
        return ++container_it_;
    }
    decltype(auto) operator--()
    {
        ++inc_counter_;
        return --container_it_;
    }

    decltype(auto) operator+=(int n)
    {
        ++inc_counter_;
        return container_it_ += n;
    }
    decltype(auto) operator-=(int n)
    {
        ++inc_counter_;
        return container_it_ -= n;
    }

    typename Container::iterator container_it_;

    int& inc_counter_;
};

template <class Container>
struct counting_container_wrapper
{
    explicit counting_container_wrapper(Container& container)
        : container_(container) {}

    auto begin()
    {
        return counting_iterator<Container>(container_.begin(), inc_counter_);
    }
    auto end()
    {
        return counting_iterator<Container>(container_.end(), inc_counter_);
    }

    void reset_inc_counter() { inc_counter_ = 0; }
    int inc_counter() const { return inc_counter_; }

    Container& container_;

    int inc_counter_ = 0;
};

TEST(InsertionToSorted, LowerBoundUpperBound)
{
    std::list<int> data(1'000'000, 1); // Change it to std::vector<int> to see the difference.

    counting_container_wrapper<decltype(data)> counting_wrapper(data);
    int compares_counter;
    const auto less_comparator = [&compares_counter](int a, int b)
    {
        ++compares_counter;
        return a < b;
    };

    counting_wrapper.reset_inc_counter();
    compares_counter = 0;
    std::lower_bound(counting_wrapper.begin(), counting_wrapper.end(), 1, less_comparator);

    // std::cout << "lower_bound: " << counting_wrapper.inc_counter() << " / " << compares_counter << std::endl;
    // GCC && Clang: lower_bound: 1999993 / 20
    EXPECT_EQ(counting_wrapper.inc_counter(), 1'999'993);
    EXPECT_EQ(compares_counter, 20);

    counting_wrapper.reset_inc_counter();
    compares_counter = 0;
    std::upper_bound(counting_wrapper.begin(), counting_wrapper.end(), 1, less_comparator);

    // std::cout << "upper_bound: " << counting_wrapper.inc_counter() << " / " << compares_counter << std::endl;
    // GCC && Clang: upper_bound: 2000000 / 19
    EXPECT_EQ(counting_wrapper.inc_counter(), 2'000'000);
    EXPECT_EQ(compares_counter, 19);
}
