#include "impl.h"

#include <bitset>
#include <iostream>

std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations)
{
    std::tuple<worker_id, worker_id, days> intersection(0, 0, 0);
    for (auto iW = workerVacations.cbegin(); iW != workerVacations.cend(); ++iW) {
        const std::bitset<daysInMonth> iVacation(iW->second, 0, daysInMonth, availableMarker, vacationMarker);

        for (auto jW = std::next(iW); jW != workerVacations.cend(); ++jW) {
            const std::bitset<daysInMonth> jVacation(jW->second, 0, daysInMonth, availableMarker, vacationMarker);

            auto ijIntersection = iVacation & jVacation;
            if (std::get<2>(intersection) < ijIntersection.count()) {
                intersection = std::tuple<worker_id, worker_id, days>(iW->first, jW->first, ijIntersection.count());
            }
        }
    }
    return intersection;
}
