#include "impl.h"
#include <bitset>

bool isBiggerIntersection(const calendar& c1,const  calendar& c2, days& maxIntersectionCount) {
	std::bitset<daysInMonth> bitFormatCalendar1(c1, 0, c1.size(),availableMarker, vacationMarker);
	std::bitset<daysInMonth> bitFormatCalendar2(c2, 0, c2.size(),availableMarker, vacationMarker);
	days IntersectionCount =  (bitFormatCalendar1 & bitFormatCalendar2).count();
	if (IntersectionCount > maxIntersectionCount) {
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
		for (auto it = workerVacations.begin();  std::next(it) != workerVacations.end() ; ++it) {
			for (auto it2 = std::next(it); it2 != workerVacations.end() ; ++it2) {
				if (isBiggerIntersection(it->second, it2->second, maxIntersectionCount)){
					maxIntersection = std::tie(it->first, it2->first, maxIntersectionCount);
				}
			}
		}
	}
	return maxIntersection;
}
