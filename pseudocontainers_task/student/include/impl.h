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

using iterator = std::unordered_map<worker_id, calendar>::const_iterator;
void checkOverlap( int& count, int& overlap, worker_id& w1,  worker_id& w2, iterator& it, iterator& nextWorker){
    if(count > overlap){
        w1 = it->first;
        w2 = nextWorker->first;
        overlap = count;                
    }
    count = 0;    
}


std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations){
    worker_id w1 = 0, w2 = 0;
    int overlap = 0, count = 0;

    for(auto it = workerVacations.begin(); it != workerVacations.end(); ++it){
        for(auto nextWorker = workerVacations.begin(); nextWorker != workerVacations.end(); nextWorker++){
            if(it == nextWorker) continue;
            auto workerMonth = it->second;
            for(int j = 0; j<workerMonth.length(); j++){
                if(workerMonth.at(j) == 'x' && workerMonth.at(j) == nextWorker->second.at(j))
                    count++;
                else 
                    checkOverlap(count, overlap, w1, w2, it, nextWorker);             
            }
            checkOverlap(count, overlap, w1, w2, it, nextWorker);
        }   
    }
    return std::tuple<worker_id, worker_id, days> (w1, w2, overlap);
}
