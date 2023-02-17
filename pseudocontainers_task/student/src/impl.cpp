#include "impl.h"
#include <bitset>
std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations){

    worker_id resultWorker1{}, resultWorker2{};
    days resultDaysOverlap{};


    for (auto & outerVacation : workerVacations){

        std::bitset<daysInMonth> outerCalendar(outerVacation.second,0,outerVacation.second.size(),'o','x');
    
        for(auto & innerVacation : workerVacations){
            if(innerVacation!=outerVacation){
                std::bitset<daysInMonth> innerCalendar(innerVacation.second,0,innerVacation.second.size(),'o','x');
                std::bitset<daysInMonth> overlapCalendar = outerCalendar & innerCalendar;
                auto countOverlap = overlapCalendar.count();

                if(countOverlap > resultDaysOverlap){
                    resultDaysOverlap=countOverlap;
                    resultWorker1=outerVacation.first;
                    resultWorker2=innerVacation.first;

                }
            }
        }

    }

    return std::tie(resultWorker1,resultWorker2,resultDaysOverlap);
}