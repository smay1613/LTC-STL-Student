#include "maintest.h"
#include "impl.h"

using namespace ::testing;

bool isIncluded(worker_id worker, std::tuple<worker_id, worker_id, days>& intersectionData)
{
    return worker == std::get<0>(intersectionData)
           || worker == std::get<1>(intersectionData);
};

std::string generateFullCalendar()
{
    return std::string (daysInMonth, vacationMarker);
};

std::string generateEmptyCalendar()
{
    return std::string (daysInMonth, availableMarker);
};

std::string generateShiftedCalendar(size_t begin, size_t shift)
{
    std::string calendar (daysInMonth, availableMarker);
    std::fill(std::next(calendar.begin(), begin),
              std::next(calendar.begin(), shift),
              vacationMarker);
    return calendar;
}

TEST(NormalCases, WholeIntersection)
{
    const std::unordered_map<worker_id, calendar> vacationsData {
        {1, generateFullCalendar()},
        {2, generateFullCalendar()},
        {3, generateEmptyCalendar()}
    };

    auto maxIntersection = getMaxIntersection(vacationsData);

    EXPECT_TRUE(isIncluded(1, maxIntersection));
    EXPECT_TRUE(isIncluded(2, maxIntersection));
    EXPECT_EQ(std::get<2>(maxIntersection), daysInMonth);
}

TEST(NormalCases, PartIntersection)
{
    const std::unordered_map<worker_id, calendar> vacationsData {
        {1, generateShiftedCalendar(0, 7)},
        {2, generateShiftedCalendar(4, 8)},
        {3, generateShiftedCalendar(3, 7)}
    };

    auto maxIntersection = getMaxIntersection(vacationsData);

    EXPECT_TRUE(isIncluded(1, maxIntersection));
    EXPECT_TRUE(isIncluded(3, maxIntersection));
    EXPECT_EQ(std::get<2>(maxIntersection), 4);
}

TEST(NormalCases, PartIntersection_2)
{
    const std::unordered_map<worker_id, calendar> vacationsData {
        {1, generateShiftedCalendar(0, 7)},
        {2, generateShiftedCalendar(1, 8)},
        {3, generateShiftedCalendar(1, 8)}
    };

    auto maxIntersection = getMaxIntersection(vacationsData);

    EXPECT_TRUE(isIncluded(2, maxIntersection));
    EXPECT_TRUE(isIncluded(3, maxIntersection));
    EXPECT_EQ(std::get<2>(maxIntersection), 7);
}

TEST(NormalCases, PartIntersection_3)
{
    const std::unordered_map<worker_id, calendar> vacationsData {
        {1, generateShiftedCalendar(0, 13)},
        {2, generateShiftedCalendar(8, 22)},
        {3, generateShiftedCalendar(15, 25)}
    };

    auto maxIntersection = getMaxIntersection(vacationsData);

    EXPECT_TRUE(isIncluded(3, maxIntersection));
    EXPECT_TRUE(isIncluded(2, maxIntersection));
    EXPECT_EQ(std::get<2>(maxIntersection), 7);
}

TEST(CornerCases, NoIntersection)
{
    const std::unordered_map<worker_id, calendar> vacationsData {
        {1, generateFullCalendar()},
        {2, generateEmptyCalendar()}
    };

    auto maxIntersection = getMaxIntersection(vacationsData);

    EXPECT_FALSE(isIncluded(1, maxIntersection));
    EXPECT_FALSE(isIncluded(2, maxIntersection));
    EXPECT_EQ(std::get<2>(maxIntersection), 0);
}

TEST(CornerCases, Empty)
{
    const std::unordered_map<worker_id, calendar> vacationsData {
    };

    auto maxIntersection = getMaxIntersection(vacationsData);

    EXPECT_EQ(std::get<2>(maxIntersection), 0);
}
