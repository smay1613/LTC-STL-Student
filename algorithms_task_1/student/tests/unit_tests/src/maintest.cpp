#include "maintest.h"
#include <forward_list>

using namespace ::testing;

size_t groupsCount(const std::vector<size_t>& data)
{
    size_t groupsCount {};
    for(auto groupEndIt = data.begin();
        groupEndIt != data.end();)
    {
        auto groupStartIt = groupEndIt;
        std::tie(groupStartIt, groupEndIt) = consecutive_group(groupEndIt, data.end());
        if (groupStartIt != data.end())
        {
            ++groupsCount;
        }
    }
    return groupsCount;
}

template<class T>
std::vector<std::pair<size_t, size_t>> groupsPositions(const T& data)
{
    std::vector<std::pair<size_t, size_t>> groupsPositions;

    for(auto groupEndIt = data.begin();
        groupEndIt != data.end();)
    {
        auto groupStartIt = groupEndIt;
        std::tie(groupStartIt, groupEndIt) = consecutive_group(groupEndIt, data.end());
        if (groupStartIt != data.end())
        {
            groupsPositions.emplace_back(std::distance(data.begin(), groupStartIt),
                                         std::distance(data.begin(), groupEndIt));
        }
    }
    return groupsPositions;
}

TEST(GroupsCount, NoGroupsOneEntry)
{
    const std::vector<size_t> data {1};

    EXPECT_EQ(groupsCount(data), 0);
}

TEST(GroupsCount, NoGroupsNoEntry)
{
    const std::vector<size_t> data {};

    EXPECT_EQ(groupsCount(data), 0);
}

TEST(GroupsCount, OneGroupNormal)
{
    const std::vector<size_t> data {1, 2, 1, 1};

    EXPECT_EQ(groupsCount(data), 1);
}

TEST(GroupsCount, NoGroupsManyEntry)
{
    const std::vector<size_t> data {9, 1, 7, 8, 5, 6, 7, 4, 3};

    EXPECT_EQ(groupsCount(data), 0);
}

TEST(GroupsCount, ManyGroupsNormal)
{
    const std::vector<size_t> data {9, 9, 8, 8, 8, 6, 7, 7, 7};

    EXPECT_EQ(groupsCount(data), 3);
}

TEST(Positions, ManyGroupsNormal)
{
    const std::vector<size_t> data {9, 9, 8, 8, 8, 6, 7, 7, 7};

    auto positions = groupsPositions(data);
    EXPECT_EQ(positions.size(), 3);

    std::vector<std::pair<size_t, size_t>> expectedGroups {
        std::pair<size_t, size_t>{0, 2},
        std::pair<size_t, size_t>{2, 5},
        std::pair<size_t, size_t>{6, 9}
    };

    EXPECT_EQ(positions, expectedGroups);
}

TEST(Positions, OneGroupNormal)
{
    const std::vector<size_t> data {9, 3, 3, 3, 7};

    auto positions = groupsPositions(data);
    EXPECT_EQ(positions.size(), 1);

    std::vector<std::pair<size_t, size_t>> expectedGroups {
        std::pair<size_t, size_t>{1, data.size() - 1}
    };

    EXPECT_EQ(positions, expectedGroups);
}

TEST(ContainerType, OneGroupNormal)
{
    const std::forward_list<size_t> data {9, 3, 3, 3, 7};

    auto positions = groupsPositions(data);
    EXPECT_EQ(positions.size(), 1);

    std::vector<std::pair<size_t, size_t>> expectedGroups {
        std::pair<size_t, size_t>{1, 4}
    };

    EXPECT_EQ(positions, expectedGroups);
}
