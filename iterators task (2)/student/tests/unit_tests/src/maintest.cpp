#include "maintest.h"
#include <list>

using namespace ::testing;

TEST_F(TypesAndTraits, Properties)
{
    static_assert(std::is_same<
                  key_iterator,
                  pair_iterator<iterator, true>>::value,
                  "Do not change key iterator type!");

    static_assert(std::is_same<
                  value_iterator,
                  pair_iterator<iterator, false>>::value,
                  "Do not change value iterator type!");
}

GENERATE_HAS_MEMBER_TYPE(value_type)
GENERATE_HAS_MEMBER_TYPE(reference)
GENERATE_HAS_MEMBER_TYPE(pointer)
GENERATE_HAS_MEMBER_TYPE(iterator_category)
GENERATE_HAS_MEMBER_TYPE(difference_type)

TEST_F(TypesAndTraits, Traits)
{
    static_assert (has_member_type_value_type<key_iterator>::value,
                   "Traits are not provided for key iterator!");
    static_assert (has_member_type_pointer<key_iterator>::value,
                   "Traits are not provided for key iterator!");
    static_assert (has_member_type_reference<key_iterator>::value,
                   "Traits are not provided for key iterator!");
    static_assert (has_member_type_iterator_category<key_iterator>::value,
                   "Traits are not provided for key iterator!");
    static_assert (has_member_type_difference_type<key_iterator>::value,
                   "Traits are not provided for key iterator!");

    static_assert (has_member_type_value_type<value_iterator>::value,
                   "Traits are not provided for value iterator!");
    static_assert (has_member_type_pointer<value_iterator>::value,
                   "Traits are not provided for value iterator!");
    static_assert (has_member_type_reference<value_iterator>::value,
                   "Traits are not provided for value iterator!");
    static_assert (has_member_type_iterator_category<value_iterator>::value,
                   "Traits are not provided for value iterator!");
    static_assert (has_member_type_difference_type<value_iterator>::value,
                   "Traits are not provided for value iterator!");
}

TEST_F(TypesAndTraits, ValueTypeTraits)
{
    static_assert (std::is_same<const key_type,
                                key_iterator::value_type>::value,
                   "Expected correct key value_type trait");

    static_assert (std::is_same<value_type,
                                value_iterator::value_type>::value,
                   "Expected correct key type property");
}

TEST_F(Usage, BasicAssign)
{
    auto keysView = make_keys_view(data);
    std::vector<std::string> keys {keysView.begin(),
                                   keysView.end()};


    auto valuesView = make_values_view(data);
    std::list<size_t> values {valuesView.begin(),
                                valuesView.end()};

    EXPECT_EQ(data.size(), keys.size());
    EXPECT_EQ(data.size(), values.size());
}

TEST_F(Usage, BasicAlgorithm)
{
    std::vector<std::string> keys {};
    std::copy(make_key_iterator(data.begin()),
              make_key_iterator(data.end()),
              std::back_inserter(keys));

    std::list<size_t> values;
    std::reverse_copy(make_value_iterator(data.begin()),
                      make_value_iterator(data.end()),
                      std::back_inserter(values));

    EXPECT_EQ(data.size(), keys.size());
    EXPECT_EQ(data.size(), values.size());

}

TEST_F(Usage, BasicRangeFor)
{
    for (auto& key : make_keys_view(data))
    {
        bool canAssign = std::is_assignable<decltype (key), std::string>::value;
        EXPECT_FALSE(canAssign);
    }

    for (const auto& key : make_keys_view(data))
    {
        bool canAssign = std::is_assignable<decltype (key), std::string>::value;
        EXPECT_FALSE(canAssign);
    }

    for (const auto& value : make_values_view(data))
    {
        bool canAssign = std::is_assignable<decltype (value), size_t>::value;
        EXPECT_FALSE(canAssign);
    }

    for (auto& value : make_values_view(data))
    {
        bool canAssign = std::is_assignable<decltype (value), size_t>::value;
        EXPECT_TRUE(canAssign);
    }
}

/** @warning ADVANCED TASK! */
TEST_F(Usage, DISABLED_Const)
{
    const auto constData = data;
    for (auto& key : make_keys_view(constData))
    {
        bool canAssign = std::is_assignable<decltype (key), std::string>::value;
        EXPECT_FALSE(canAssign);
    }
    for (const auto& key : make_keys_view(constData))
    {
        bool canAssign = std::is_assignable<decltype (key), std::string>::value;
        EXPECT_FALSE(canAssign);
    }

    auto constContext = [constData]()
    {

        for (const auto& value : make_values_view(constData))
        {
            bool canAssign = std::is_assignable<decltype (value), size_t>::value;
            EXPECT_FALSE(canAssign);
        }

        for (auto& value : make_values_view(constData))
        {
            bool canAssign = std::is_assignable<decltype (value), size_t>::value;
            EXPECT_TRUE(canAssign);
        }
    };
}
