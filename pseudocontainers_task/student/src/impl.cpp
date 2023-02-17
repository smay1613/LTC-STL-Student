#include "impl.h"
#include <bitset>

days getIntersection(const calendar& c1,const  calendar& c2, days& maxIntersectionCount) {
	std::bitset<daysInMonth> bitFormatCalendar1(c1, 0, c1.size(),availableMarker, vacationMarker);
	std::bitset<daysInMonth> bitFormatCalendar2(c2, 0, c2.size(),availableMarker, vacationMarker);
	days IntersectionCount =  (bitFormatCalendar1 & bitFormatCalendar2).count();
	return std::max(IntersectionCount, maxIntersectionCount);
}

const bool isBiggerIntersection(days n1, days n2) {
	return n1 > n2;
}

std::tuple<worker_id, worker_id, days> getMaxIntersection(const std::unordered_map<worker_id, calendar>& workerVacations) {
	days maxIntersectionCount = 0;
	std::tuple<worker_id, worker_id, days> maxIntersection;
	if (!workerVacations.empty())
	{
		for (auto worker1 = workerVacations.begin();  std::next(worker1) != workerVacations.end() ; ++worker1) {
			for (auto worker2 = std::next(worker1); worker2 != workerVacations.end() ; ++worker2) {
				days IntersectionCount = getIntersection(worker1->second, worker2->second, maxIntersectionCount);
				if (isBiggerIntersection(IntersectionCount, maxIntersectionCount)){
					maxIntersectionCount = IntersectionCount;
					maxIntersection = std::tie(worker1->first, worker2->first, maxIntersectionCount);
				}
			}
		}
	}
	return maxIntersection;
}
