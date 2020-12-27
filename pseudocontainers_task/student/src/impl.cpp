#include "impl.h"

#include <bitset>
#include <iostream>

std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations)
{
    std::tuple<worker_id, worker_id, days> intersection(0, 0, 0);
    for (auto const& iWorker : workerVacations) {
        const std::bitset<daysInMonth> iVacation(iWorker.second, 0, daysInMonth, availableMarker, vacationMarker);

        for (auto const& jWorker : workerVacations) {
            if (iWorker.first == jWorker.first) {
                continue;
            }
            const std::bitset<daysInMonth> jVacation(jWorker.second, 0, daysInMonth, availableMarker, vacationMarker);
            auto ijIntersection = iVacation & jVacation;
            if (std::get<2>(intersection) < ijIntersection.count()) {
                intersection = std::make_tuple(iWorker.first, jWorker.first, ijIntersection.count());
            }
        }
    }
    return intersection;
}
