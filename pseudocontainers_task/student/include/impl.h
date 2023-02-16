#pragma once
#include <string>
#include <map>
#include <unordered_map>

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
    days vacationdaysintersect = 0;
    worker_id id1,id2;

    auto isnotthesameworker = [](const std::pair<worker_id,calendar> &worker1 , const std::pair<worker_id,calendar> &worker2)
    {
        return worker1.first != worker2.first;
    };

    auto vacationMarkeroverlap = [](const std::pair<worker_id,calendar> &worker1 , const std::pair<worker_id,calendar> &worker2 , const days &day)
    {
        return worker1.second.at(day)==worker2.second.at(day) && worker1.second.at(day) == vacationMarker;
    };

    auto maxvactionoverlap = [&](const std::pair<worker_id,calendar> &worker1 , const std::pair<worker_id,calendar> &worker2)
    {
        days vactiondays = 0;
        for(days day = 0; day < daysInMonth; day++)
        {
            if(vacationMarkeroverlap(worker1,worker2,day))
            {
                vactiondays++;
            }
        }
        return vactiondays;
    };

    for(auto const& worker1 : workerVacations)
    {
        for(auto const& worker2 : workerVacations)
        {
            if(isnotthesameworker(worker1,worker2))
            {
                days overlap = maxvactionoverlap(worker1,worker2);
                if(overlap > vacationdaysintersect)
                {
                    vacationdaysintersect = overlap;
                    id1 = worker1.first;
                    id2 = worker2.first;
                }
            }
        }
    }

    return std::make_tuple(id1,id2,vacationdaysintersect);
}
