#include "impl.h"
#include <bitset>

bool isBiggerIntersection(const calendar& c1,const  calendar& c2, days& maxIntersectionCount) {
	std::bitset<daysInMonth> bitFormatCalendar1(c1, 0, c1.size(),availableMarker, vacationMarker);
	std::bitset<daysInMonth> bitFormatCalendar2(c2, 0, c2.size(),availableMarker, vacationMarker);
	days IntersectionCount =  (bitFormatCalendar1 & bitFormatCalendar2).count();
	if (std::max(IntersectionCount, maxIntersectionCount) != maxIntersectionCount) {
		maxIntersectionCount = IntersectionCount;
		return true;
	}
	return false;
}

std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations) {
	days maxIntersectionCount = 0;
	std::tuple<worker_id, worker_id, days> maxIntersection;
	if (!workerVacations.empty())
	{
		for (auto worker1 = workerVacations.begin();  std::next(worker1) != workerVacations.end() ; ++worker1) {
			for (auto worker2 = std::next(worker1); worker2 != workerVacations.end() ; ++worker2) {
				if (isBiggerIntersection(worker1->second, worker2->second, maxIntersectionCount)){
					maxIntersection = std::tie(worker1->first, worker2->first, maxIntersectionCount);
				}
			}
		}
	}
	return maxIntersection;
}
