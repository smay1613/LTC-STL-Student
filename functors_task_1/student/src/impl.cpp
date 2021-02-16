#include "impl.h"

#include <algorithm>
#include <forward_list>
#include <map>
#include <utility>


BeerBrand BeerOrganizer::operator()()
{
    if (m_nextBeer >= m_end)
    {
        m_nextBeer = m_begin;
    }

    return static_cast<BeerBrand>(m_nextBeer++);
}

bool isExpensiveBeer(const BeerBrand brand)
{
    return (BeerBrand::Corona == brand) || (BeerBrand::HoeGaarden == brand);
}

Cocktail MixingPolicy::mix(const AlcoholDrink lhd, const NonAlcoholDrink rhd)
{
    auto result = Cocktail::Oops;

    switch (lhd)
    {
    case AlcoholDrink::Gin :
        if (NonAlcoholDrink::LimeJuice == rhd)
        {
            result = Cocktail::Gimlet;
        }
        else if (NonAlcoholDrink::GrapefruitJuice == rhd)
        {
            result = Cocktail::Greyhount;
        }
        break;
    case AlcoholDrink::Whiskey :
        if (NonAlcoholDrink::SevenUp == rhd)
        {
            result = Cocktail::SevenPlusSeven;
        }
        break;
    case AlcoholDrink::Beer :
    case AlcoholDrink::Wine :
    default:
        break;
    }

    return result;
}
