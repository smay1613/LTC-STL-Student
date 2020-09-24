#include "impl.h"

BeerBrand BeerOrganizer::operator()()
{
    if (currentBeerIndex == static_cast<int>(BeerBrand::Max))
    {
        currentBeerIndex = 1;
    }
    return static_cast<BeerBrand>(currentBeerIndex++);
}

