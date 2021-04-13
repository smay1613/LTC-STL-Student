#pragma once
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
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
std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations) {
    std::tuple<worker_id, worker_id, days> result;

    for (auto workerItr  = workerVacations.begin(); workerItr != workerVacations.end(); ++workerItr) {
        std::for_each (std::next(workerItr), workerVacations.end(), [&](const std::pair<worker_id, calendar>& workerCalendar) {
            std::bitset<daysInMonth> worker1Calendar(workerItr->second, 0, workerItr->second.size(), availableMarker, vacationMarker);
            std::bitset<daysInMonth> worker2Calendar(workerCalendar.second, 0, workerCalendar.second.size(), availableMarker, vacationMarker);

            days commonVacations = (worker1Calendar & worker2Calendar).count();

            if (commonVacations > std::get<2>(result)) {
                result = std::make_tuple(workerItr->first, workerCalendar.first, commonVacations);
            }

        });
    }

    return result;
}
