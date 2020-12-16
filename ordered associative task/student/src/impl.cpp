#include "impl.h"

size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
   std::map<size_t, size_t> ranges{{29, 1}, {49, 2}, {69, 3}, {89, 4}};
   const auto it = ranges.lower_bound(markIn100Point);
   return it == ranges.end() ? 5 : it->second;
}
