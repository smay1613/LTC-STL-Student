#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <bitset>
#include <iostream>

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
std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations){
    days max_intersection = 0;
    worker_id worker1, worker2;

    for( auto worker: workerVacations){
        for( auto other_worker: workerVacations){

            if( worker != other_worker){
                
                std::bitset<30> calendar1(worker.second, 0, 30, availableMarker, vacationMarker);
                std::bitset<30> calendar2(other_worker.second, 0, 30, availableMarker, vacationMarker);

                days intersection = (calendar1 & calendar2).count();

                if(intersection > max_intersection){
                    max_intersection = intersection;
                    worker1 = worker.first;
                    worker2 = other_worker.first;
                }    
            }
        }
    }

    return std::tie(worker1, worker2, max_intersection);
}
