#include "impl.h"

#include <algorithm>
#include <bitset>

std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations)
{
    std::tuple<worker_id, worker_id, days> result;

    std::for_each(workerVacations.begin(), workerVacations.end(), [&](const std::pair<worker_id, calendar>& currentWorkerVacation) {
        auto firstworker = workerVacations.find(currentWorkerVacation.first);
        std::for_each(++firstworker, workerVacations.end(),[&](const std::pair<worker_id, calendar>& nextWorkerVacation) {
            const std::bitset<daysInMonth> calendar1(currentWorkerVacation.second, 0, daysInMonth, availableMarker, vacationMarker);
            const std::bitset<daysInMonth> calendar2(nextWorkerVacation.second, 0, daysInMonth, availableMarker, vacationMarker);

            const days countOfVacationDays = (calendar1 & calendar2).count();
            if (countOfVacationDays > std::get<2>(result))
            {
                result = std::make_tuple(currentWorkerVacation.first, nextWorkerVacation.first, countOfVacationDays);
            }
        });
    });

    return result;
}
