#include "impl.h"

BeerBrand BeerOrganizer::operator()()
{
    if((counter + 1) >= static_cast<size_t>(BeerBrand::Max))
    {
        counter = static_cast<size_t>(BeerBrand::None);
    }
    return static_cast<BeerBrand>(++counter);
}

std::map <std::pair<AlcoholDrink, NonAlcoholDrink>, Cocktail> MixingPolicy::bar =
{
    {std::make_pair(AlcoholDrink::Gin, NonAlcoholDrink::LimeJuice), Cocktail::Gimlet},
    {std::make_pair(AlcoholDrink::Gin, NonAlcoholDrink::GrapefruitJuice), Cocktail::Greyhount},
    {std::make_pair(AlcoholDrink::Whiskey, NonAlcoholDrink::SevenUp), Cocktail::SevenPlusSeven}
};