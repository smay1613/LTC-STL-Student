#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerOrganizer():
        m_BeerBrand_id(BeerBrandNoneInt+1)
        {}

    BeerBrand operator()()
    {
        if( m_BeerBrand_id == BeerBrandMaxInt )
        {
            m_BeerBrand_id = BeerBrandNoneInt+1;
        }
        return static_cast<BeerBrand>(m_BeerBrand_id++);
    }
    static const unsigned int BeerBrandMaxInt = static_cast<int>(BeerBrand::Max);
    static const unsigned int BeerBrandNoneInt = static_cast<int>(BeerBrand::None);
private:
    int m_BeerBrand_id;
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer( const BeerBrand& _beerBrand )
{
    return (BeerBrand::Corona == _beerBrand) || (BeerBrand::HoeGaarden == _beerBrand);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand& l_beerBrand, const BeerBrand& r_beerBrand)
{
    return getBeerCountry( l_beerBrand ) == getBeerCountry( r_beerBrand );
};

struct MixingPolicy
{
    /**
     * @todo Implement static transformator function
     * @return crafted cocktail
     *
     * @note Cookbook:
     * Gin + Lime juice = Gimlet;
     * Gin + Grapefruit juice = Greyhount;
     * Whiskey + SevenUp = SevenPlusSeven;
     * Others + Others = Oops;
     */
    static Cocktail mix(const AlcoholDrink& alcohol, const NonAlcoholDrink& nonAlcohol)
    {
        Cocktail mixedCocktail = Cocktail::Oops;
        if( AlcoholDrink::Gin == alcohol )
        {
            if( NonAlcoholDrink::LimeJuice == nonAlcohol)
                mixedCocktail = Cocktail::Gimlet;
            else if( NonAlcoholDrink::GrapefruitJuice == nonAlcohol )
                mixedCocktail = Cocktail::Greyhount;
        }
        else if( AlcoholDrink::Whiskey == alcohol )
        {
            if( NonAlcoholDrink::SevenUp == nonAlcohol )
                mixedCocktail = Cocktail::SevenPlusSeven;
        }
        return mixedCocktail;
    }
};

std::function<Cocktail(const AlcoholDrink& alcohol, const NonAlcoholDrink& nonAlcohol)> mixer {&MixingPolicy::mix};
