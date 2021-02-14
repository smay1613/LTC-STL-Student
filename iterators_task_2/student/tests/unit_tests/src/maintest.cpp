#include "maintest.h"
#include "impl.h"
#include <numeric>
#include <forward_list>
#include <list>
#include <deque>

using namespace ::testing;

TEST(StringAccumulate, AccumulateEqual)
{
    std::string result;

    std::vector<std::string> dataToConcatenate {"one",
                                                "two",
                                                "three",
                                                "four"};

    std::copy(dataToConcatenate.begin(), dataToConcatenate.end(),
              make_accumulator(result));

    std::string expected {std::accumulate(dataToConcatenate.begin(), dataToConcatenate.end(),
                                           std::string {})};

    EXPECT_EQ(expected, result);
}

TEST(StringAccumulate, Forward)
{
    std::string result;

    std::forward_list<std::string> dataToConcatenate {"one",
                                                      "two",
                                                      "three",
                                                      "four"};

    std::copy(dataToConcatenate.begin(), dataToConcatenate.end(),
              make_accumulator(result));

    std::string expected {std::accumulate(dataToConcatenate.begin(), dataToConcatenate.end(),
                                           std::string {})};

    EXPECT_EQ(expected, result);
}

struct move_only
{
    move_only() = default;
    move_only(move_only&&)
        : moved {true} {
    }
    move_only& operator=(move_only&&) {
        moved = true;
        return *this;
    }
    bool moved {false};
};

TEST(Accumulate, RValues)
{
    std::vector<move_only> result;
    const auto internalEntrySize = 10;

    std::vector<std::vector<move_only>> dataToConcatenate;
    dataToConcatenate.resize(internalEntrySize);
    for (auto& entry : dataToConcatenate)
    {
        entry.resize(internalEntrySize);
    }

    std::copy(std::make_move_iterator(dataToConcatenate.begin()),
              std::make_move_iterator(dataToConcatenate.end()),
              make_accumulator(result));

    EXPECT_EQ(result.size(), internalEntrySize * dataToConcatenate.size());
    EXPECT_TRUE(std::all_of(result.begin(), result.end(), [](const move_only& object) {
        return object.moved;
    }));
}

TEST(Accumulate, OtherContainerRvalue)
{
    std::vector<size_t> result;
    const auto internalEntrySize = 10;

    std::list<std::deque<size_t>> dataToConcatenate;
    dataToConcatenate.resize(internalEntrySize);
    for (auto& entry : dataToConcatenate)
    {
        entry.resize(internalEntrySize);
    }

    std::copy(std::make_move_iterator(dataToConcatenate.begin()),
              std::make_move_iterator(dataToConcatenate.end()),
              make_accumulator(result));

    EXPECT_EQ(result.size(), internalEntrySize * dataToConcatenate.size());
}

TEST(Accumulate, OtherContainerLvalue)
{
    std::vector<size_t> result;
    const auto internalEntrySize = 10;

    std::list<std::deque<size_t>> dataToConcatenate;
    dataToConcatenate.resize(internalEntrySize);
    for (auto& entry : dataToConcatenate)
    {
        entry.resize(internalEntrySize);
    }
    const auto constCopy = dataToConcatenate;
    std::copy(constCopy.cbegin(),
              constCopy.cend(),
              make_accumulator(result));

    EXPECT_EQ(result.size(), internalEntrySize * constCopy.size());
}

TEST(Properties, Traits)
{
    using container = std::vector<int>;
    using accumulator = accumulator<container>;
    using category = std::iterator_traits<accumulator>::iterator_category;

    static_assert (std::is_same<category, std::output_iterator_tag>::value,
                   "Wrong iterator type!");

    using reference = std::add_lvalue_reference<accumulator>::type;
    using return_type_deref = decltype(std::declval<accumulator>().operator*());
    static_assert (std::is_same<return_type_deref,
                                reference>::value,
                   "Wrong return type for dereferencing");

    using return_type_increment = decltype(std::declval<accumulator>().operator++());
    static_assert (std::is_same<return_type_increment,
                                reference>::value,
                   "Wrong return type for dereferencing");

    static_assert (std::is_trivially_copyable<accumulator>::value,
                   "Shall support trivial copying");

    using lvalue_container = std::add_lvalue_reference<container>::type;
    static_assert (std::is_assignable<accumulator,
                                      lvalue_container>::value,
                   "Shall support container assign (lvalue)");

    using rvalue_container = std::add_rvalue_reference<container>::type;
    static_assert (std::is_assignable<accumulator,
                                      rvalue_container>::value,
                   "Shall support container assign (rvalue)");

    using another_container = std::deque<int>;
    using const_ref_another = std::add_lvalue_reference<std::add_const<another_container>::type>::type;
    static_assert (std::is_assignable<accumulator,
                                      const_ref_another>::value,
                   "Shall support another container assign (lvalue)");
}
