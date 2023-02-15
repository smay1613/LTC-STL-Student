#include "impl.h"
#include <bitset>

std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations) {
    std::tuple<worker_id, worker_id, days> result = std::make_tuple(0, 0, 0);

    for (auto const &first_worker : workerVacations) {
        for (auto const &second_worker : workerVacations) {
            if (first_worker != second_worker) {
                std::bitset<daysInMonth> first_worker_vacation(first_worker.second, 0, first_worker.second.size(), availableMarker, vacationMarker);
                std::bitset<daysInMonth> second_worker_vacation(second_worker.second, 0, first_worker.second.size(), availableMarker, vacationMarker);
                int intersectedDays = (first_worker_vacation & second_worker_vacation).count();

                if (intersectedDays > std::get<2>(result)) {
                    result = std::make_tuple(first_worker.first, second_worker.first, intersectedDays);
                }
            }
        }
    }

    return result;
}
