#include "impl.h"

BeerOrganizer::BeerOrganizer()
   : currentBeerBand((int)BeerBrand::None)
{}

BeerBrand BeerOrganizer::operator()()
{
    if (++currentBeerBand == (int)BeerBrand::Max) {
        currentBeerBand = (int)BeerBrand::None;
        currentBeerBand++;
    }

    return (BeerBrand)currentBeerBand;
}

bool isExpensiveBeer(const BeerBrand beerBrand)
{
    if (beerBrand == BeerBrand::Corona || beerBrand == BeerBrand::HoeGaarden)
        return true;
    return false;
}
