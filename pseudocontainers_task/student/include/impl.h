#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <bitset>

using calendar = std::string; // format: o - available, x - vacation
using worker_id = size_t;
using days = size_t;
constexpr days daysInMonth = 30;
constexpr char availableMarker = 'o';
constexpr char vacationMarker = 'x';

/**
 * @todo Implement function that will return two workers, which vacations are most intersected
 *
 * @param workerVacations - pairs of worker and his calendar
 * @return Max intersection of two workers and intersection days count
 */
std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations)
{
    std::tuple<worker_id, worker_id, days> result;

    auto getCountOfIntersectedVacationDays = [](const calendar& calendar1, const calendar& calendar2)
    {
        const std::bitset<daysInMonth> bitCalendar1(calendar1, 0, daysInMonth, availableMarker, vacationMarker);
        const std::bitset<daysInMonth> bitCalendar2(calendar2, 0, daysInMonth, availableMarker, vacationMarker);
        return (bitCalendar1 & bitCalendar2).count();
    };

    for (const auto& workerVacation : workerVacations)
    {
        std::for_each(++workerVacations.find(workerVacation.first), workerVacations.end(),
                      [&](const std::pair<worker_id, calendar>& nextWorkerVacation)
        {
            const days countOfIntersectedVacationDays = getCountOfIntersectedVacationDays(workerVacation.second, nextWorkerVacation.second);
            if (countOfIntersectedVacationDays > std::get<2>(result))
            {
                result = std::make_tuple(workerVacation.first, nextWorkerVacation.first, countOfIntersectedVacationDays);
            }
        });
    }

    return result;
}
