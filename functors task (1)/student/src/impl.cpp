#include "impl.h"

BeerBrand BeerOrganizer::operator()()
{
    if (index >= static_cast<int32_t>(BeerBrand::Max)) {
        index = static_cast<int32_t>(BeerBrand::HoeGaarden);
    }
    return static_cast<BeerBrand>(index++);
}