#pragma once
#include <iostream>
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
std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations)
{
    using CalendarList = std::bitset<daysInMonth>;
    days vacationdaysintersect = 0,overlap=0;
    worker_id id1,id2;

    for(auto const& worker1 : workerVacations)
    {
        for(auto const& worker2 : workerVacations)
        {
            if(worker1 != worker2)
            {
                CalendarList vacationcalendar1(worker1.second,0,daysInMonth,availableMarker,vacationMarker);
                CalendarList vacationcalendar2(worker2.second,0,daysInMonth,availableMarker,vacationMarker);
                overlap = (vacationcalendar1&vacationcalendar2).count();
                if(vacationdaysintersect < overlap)
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
