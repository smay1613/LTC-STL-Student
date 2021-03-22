#include "impl.h"

const std::map<size_t, size_t> bounds {
  {0, 1},
  {30, 2},
  {50, 3},
  {70, 4},
  {90, 5}
};

size_t convertMarkTo5PointSystem(size_t markIn100Point)
{
    return (--bounds.upper_bound(markIn100Point))->second;
}
