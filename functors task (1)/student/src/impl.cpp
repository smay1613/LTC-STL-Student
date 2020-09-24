#include "impl.h"

BeerBrand BeerOrganizer::operator()()
{
    if (currentBeerIndex == static_cast<size_t>(BeerBrand::Max))
    {
        currentBeerIndex = static_cast<size_t>(BeerBrand::HoeGaarden);
    }
    return static_cast<BeerBrand>(currentBeerIndex++);
}

