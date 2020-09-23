#include "impl.h"

constexpr int count = 6;
BeerBrand states[count] = { BeerBrand::HoeGaarden, BeerBrand::Corona, BeerBrand::Carlsberg, BeerBrand::Bud, BeerBrand::ZlataPraha, BeerBrand::Leffe };

BeerBrand BeerOrganizer::operator()()
{
    BeerBrand ret = states[current%count];
    current++;
    return ret;
}

Cocktail MixingPolicy::mix(AlcoholDrink alcoDrink, NonAlcoholDrink nonAlcoDrink)
{
    if (alcoDrink == AlcoholDrink::Gin && nonAlcoDrink == NonAlcoholDrink::LimeJuice)
        return Cocktail::Gimlet;
    if (alcoDrink == AlcoholDrink::Gin && nonAlcoDrink == NonAlcoholDrink::GrapefruitJuice)
        return Cocktail::Greyhount;
    if (alcoDrink == AlcoholDrink::Whiskey && nonAlcoDrink == NonAlcoholDrink::SevenUp)
        return Cocktail::SevenPlusSeven;
    return Cocktail::Oops;
}