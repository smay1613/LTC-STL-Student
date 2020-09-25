#include "impl.h"

BeerBrand BeerOrganizer::operator()() {
  if (BeerBrand::Max == static_cast<BeerBrand>(++_current)) {
    _current = 1;
  }
  return static_cast<BeerBrand>(_current);
}
