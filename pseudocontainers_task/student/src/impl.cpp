#include "impl.h"
#include <bitset>
std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations){

    worker_id resultWorker1, resultWorker2;
    days resultDaysOverlap=0;


    for (auto & itOuter : workerVacations){

        std::bitset<daysInMonth> bitsetOuter(itOuter.second,0,itOuter.second.size(),'o','x');
    
        for(auto & itInner : workerVacations){
            if(itInner!=itOuter){
                std::bitset<daysInMonth> bitsetInner(itInner.second,0,itInner.second.size(),'o','x');
                std::bitset<daysInMonth> bitsetOverlap = bitsetOuter & bitsetInner;
                auto countOverlap = bitsetOverlap.count();

                if(countOverlap > resultDaysOverlap){
                    resultDaysOverlap=countOverlap;
                    resultWorker1=itOuter.first;
                    resultWorker2=itInner.first;

                }
            }
        }

    }

    return std::tie(resultWorker1,resultWorker2,resultDaysOverlap);
}