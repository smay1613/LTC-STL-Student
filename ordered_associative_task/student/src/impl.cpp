#include "impl.h"
#include <map>

size_t convertMarkTo5PointSystem(size_t markIn100Point) {
	const size_t MAX = 100;
	std::map<int, int> ranges {
		{29, 1},
		{49, 2},
		{69, 3},
		{89, 4},
		{MAX, 5}
	};
	auto nearestRange = ranges.lower_bound(markIn100Point);
	const bool isOutOfBound = nearestRange == ranges.end();
	return isOutOfBound? ranges[MAX] : nearestRange->second;
}