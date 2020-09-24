#include "impl.h"

constexpr int BeerOrganizer::MIN = static_cast<int>(BeerBrand::None);
constexpr int BeerOrganizer::MAX = static_cast<int>(BeerBrand::Max) - 1;

BeerBrand BeerOrganizer::operator()()
{
    if (currentIndex == MAX)
    {
        currentIndex = MIN;
    }
    return static_cast<BeerBrand>(++currentIndex);
}

Cocktail MixingPolicy::mix(AlcoholDrink alcoholDrink, NonAlcoholDrink nonAlcoholDrink)
{
    auto cocktail = Cocktail::Oops;

    if (AlcoholDrink::Gin == alcoholDrink &&
        NonAlcoholDrink::LimeJuice == nonAlcoholDrink)
    {
        cocktail = Cocktail::Gimlet;
    }
    else if (AlcoholDrink::Gin == alcoholDrink &&
        NonAlcoholDrink::GrapefruitJuice == nonAlcoholDrink)
    {
        cocktail = Cocktail::Greyhount;
    }
    else if (AlcoholDrink::Whiskey == alcoholDrink &&
        NonAlcoholDrink::SevenUp == nonAlcoholDrink)
    {
        cocktail = Cocktail::SevenPlusSeven;
    }

    return cocktail;
}
