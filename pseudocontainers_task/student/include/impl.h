#pragma once
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

using iterator = std::unordered_map<worker_id, calendar>::const_iterator;
void checkOverlap( int& count, int& overlap, worker_id& w1,  worker_id& w2, iterator& it, iterator& nextWorker){
    if(count > overlap){
        w1 = it->first;
        w2 = nextWorker->first;
        overlap = count;                
    }
    count = 0;    
}

std::string convertString(const calendar& s){
    std::string result;
    for(auto& c : s) 
        (c == 'o') ? result.push_back('0') : result.push_back('1');
    return result;
}

std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations){
     worker_id w1 = 0, w2 = 0;
    int overlap = 0, count = 0;

    for(auto it = workerVacations.begin(); it != workerVacations.end(); ++it){
        std::bitset<daysInMonth> monthW1 (convertString(it->second));
        for(auto nextWorker = workerVacations.begin(); nextWorker != workerVacations.end(); nextWorker++){
            if(it == nextWorker) 
                continue;
            std::bitset<daysInMonth> monthW2 (convertString(nextWorker->second));
            for(int j = 0; j<monthW1.size(); j++){
                if(monthW1[j] == 1 && monthW1[j] == monthW2[j])
                    count++;
                else 
                    checkOverlap(count, overlap, w1, w2, it, nextWorker);             
            }
            checkOverlap(count, overlap, w1, w2, it, nextWorker);
        }
    }
    return std::tuple<worker_id, worker_id, days> (w1, w2, overlap);
}
