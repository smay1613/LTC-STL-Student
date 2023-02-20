#include "impl.h"
#include <algorithm>

bool startsWith(const std::string& source, const std::string& prefix) {
	return std::search(source.begin(), source.end(), prefix.begin(), prefix.end()) == source.begin();
}
