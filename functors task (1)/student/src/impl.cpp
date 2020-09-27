#include "impl.h"
#include <array>

constexpr int count = static_cast<int>(BeerBrand::Max) - 1;
std::array<BeerBrand, count> states = { BeerBrand::HoeGaarden, BeerBrand::Corona, BeerBrand::Carlsberg, BeerBrand::Bud, BeerBrand::ZlataPraha, BeerBrand::Leffe };

BeerBrand BeerOrganizer::operator()()
{
    BeerBrand ret = states[current % count];
    current++;
    return ret;
}

Cocktail MixingPolicy::mix(AlcoholDrink alcoDrink, NonAlcoholDrink nonAlcoDrink)
{
    Cocktail result = Cocktail::Oops;
    switch (nonAlcoDrink)
    {
    case NonAlcoholDrink::LimeJuice:
        if (alcoDrink == AlcoholDrink::Gin) { result = Cocktail::Gimlet; }
        break;
    case NonAlcoholDrink::GrapefruitJuice:
        if (alcoDrink == AlcoholDrink::Gin) { result = Cocktail::Greyhount; }
        break;
    case NonAlcoholDrink::SevenUp:
        if (alcoDrink == AlcoholDrink::Whiskey) { result = Cocktail::SevenPlusSeven; }
        break;
    default:
        break;
    }
    return result;
}