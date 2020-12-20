#include "impl.h"
#include <bitset>


/*
#include <string>
#include <map>
#include <unordered_map>

using calendar = std::string; // format: o - available, x - vacation
using worker_id = size_t;
using days = size_t;
constexpr days daysInMonth = 30;
constexpr char availableMarker = 'o';
constexpr char vacationMarker = 'x';
*/

/**
 * @todo Implement function that will return two workers, which vacations are most intersected
 *
 * @param workerVacations - pairs of worker and his calendar
 * @return Max intersection of two workers and intersection days count
 */
std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations)
{
    using tWorkers = std::tuple<worker_id, worker_id>;

    std::map<days, tWorkers> intersectionsOfWorkers;

    for(auto itFirst = workerVacations.begin(); itFirst !=workerVacations.end(); ++itFirst)
    {
        for(auto itSecond = std::next( itFirst) ; itSecond !=workerVacations.end(); ++itSecond)
        {
            std::bitset<daysInMonth> intersection(itFirst->second, 0, daysInMonth, 'o', 'x');
            intersection &= std::bitset<daysInMonth>(itSecond->second, 0, daysInMonth, 'o', 'x') ;
            if(intersection.count() > 0)
            {
                intersectionsOfWorkers[intersection.count()] = std::make_tuple(itFirst->first, itSecond->first);
            }
        }
    }
    if(!intersectionsOfWorkers.empty())
    {
        auto top = intersectionsOfWorkers.rbegin();
        return { std::get<0>(top->second),
                 std::get<1>(top->second),
                 top->first };
    }
    return {0, 0, 0};
}
