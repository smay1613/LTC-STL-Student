#include "impl.h"
#include <map>

size_t convertMarkTo5PointSystem(size_t markIn100Point) {
	std::map<int, int> ranges {
		{0, 1}, {30, 2}, {50, 3}, {70, 4}, {90, 5}
	};
	auto nearestRange = ranges.equal_range(markIn100Point);
	if (nearestRange.first->second == nearestRange.second->second)
		return (--nearestRange.first)->second ;
	return nearestRange.first->second;
}