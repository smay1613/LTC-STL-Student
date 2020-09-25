#include "impl.h"

BeerBrand BeerOrganizer::operator()()
{
    BeerBrand bb = BeerBrand::HoeGaarden;

    bb = (BeerBrand)i;  
    
    (i < static_cast<int>(BeerBrand::Max) - 1) ? i++ : i = 1;
        
    return bb;
}

Cocktail MixingPolicy::mix(AlcoholDrink ad, NonAlcoholDrink nad)
{
    if(ad == AlcoholDrink::Gin && nad == NonAlcoholDrink::LimeJuice)
    {
        return Cocktail::Gimlet;
    }
    else if(ad == AlcoholDrink::Gin && nad == NonAlcoholDrink::GrapefruitJuice)
    {
        return Cocktail::Greyhount;
    }
    else if(ad == AlcoholDrink::Whiskey && nad == NonAlcoholDrink::SevenUp)
    {
        return Cocktail::SevenPlusSeven;
    }
    else
    {
        return Cocktail::Oops;
    }
}