#include "impl.h"

BeerBrand BeerOrganizer::operator()()
{
    currentBeerBrand++;

    if (currentBeerBrand == static_cast<size_t>(BeerBrand::Max)) {
        currentBeerBrand = static_cast<size_t>(BeerBrand::None);
        currentBeerBrand++;
    }

    return static_cast<BeerBrand>(currentBeerBrand);
}

bool isExpensiveBeer(const BeerBrand beerBrand)
{
    return beerBrand == BeerBrand::Corona || beerBrand == BeerBrand::HoeGaarden;
}
