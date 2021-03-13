#include "maintest.h"

using namespace ::testing;

TEST(Rotate, LeftSimple)
{
    std::list<size_t> data {0, 1, 2, 3, 4, 5};
    std::list<size_t> data_copy {data};
    // 0 is moved to the end
    rotate(data, data.begin(), std::next(data.begin()), data.end());

    std::list<size_t> expected {1, 2, 3, 4, 5, 0};
    EXPECT_EQ(data, expected);

    std::rotate(data_copy.begin(), std::next(data_copy.begin()), data_copy.end());
    EXPECT_EQ(data, data_copy);
}

TEST(Rotate, RightSimple)
{
    std::list<size_t> data {0, 1, 2, 3, 4, 5};
    std::list<size_t> data_copy {data};
    // 5 moved to the begin
    rotate(data, data.begin(), std::prev(data.end()), data.end());

    std::list<size_t> expected {5, 0, 1, 2, 3, 4};
    EXPECT_EQ(data, expected);

    std::rotate(data_copy.begin(), std::prev(data_copy.end()), data_copy.end());
    EXPECT_EQ(data, data_copy);
}

TEST(Rotate, 3Left)
{
    std::list<size_t> data {0, 1, 2, 3, 4, 5};
    std::list<size_t> data_copy {data};
    // 0 - 2 are moved to the end
    rotate(data, data.begin(), std::next(data.begin(), 3), data.end());

    std::list<size_t> expected {3, 4, 5, 0, 1, 2};
    EXPECT_EQ(data, expected);

    std::rotate(data_copy.begin(), std::next(data_copy.begin(), 3), data_copy.end());
    EXPECT_EQ(data, data_copy);
}

TEST(Rotate, 2Left)
{
    std::list<size_t> data {0, 1, 2, 3, 4, 5};
    std::list<size_t> data_copy {data};
    // 0 - 1 are moved to the end
    rotate(data, data.begin(), std::next(data.begin(), 2), data.end());

    std::list<size_t> expected {2, 3, 4, 5, 0, 1};
    EXPECT_EQ(data, expected);

    std::rotate(data_copy.begin(), std::next(data_copy.begin(), 2), data_copy.end());
    EXPECT_EQ(data, data_copy);
}

TEST(Rotate, 2Right)
{
    std::list<size_t> data {0, 1, 2, 3, 4, 5};
    std::list<size_t> data_copy {data};
    // 4-5 moved to the begin
    rotate(data, data.begin(), std::prev(data.end(), 2), data.end());

    std::list<size_t> expected {4, 5, 0, 1, 2, 3};
    EXPECT_EQ(data, expected);

    std::rotate(data_copy.begin(), std::prev(data_copy.end(), 2), data_copy.end());
    EXPECT_EQ(data, data_copy);
}

TEST(Rotate, NoMove)
{
    struct NoMove {
        NoMove() = default;
        NoMove(NoMove&&) = delete;
        NoMove& operator=(NoMove&&) = delete;
    };

    std::list<NoMove> data (5);
    rotate(data, data.begin(), std::prev(data.end(), 2), data.end());
}
