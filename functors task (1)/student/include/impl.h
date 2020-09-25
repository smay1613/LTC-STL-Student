#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    size_t index{static_cast<size_t>(BeerBrand::None) + 1};
    BeerBrand operator()()
    {
        if( index == static_cast<size_t>(BeerBrand::Max) )
        {
            index = static_cast<size_t>(BeerBrand::None) + 1;
        }
        return static_cast<BeerBrand>(index++);
    }
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand brand)
{
    return (brand == BeerBrand::Corona || brand == BeerBrand::HoeGaarden);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand lhs, BeerBrand rhs) -> bool
{
    return getBeerCountry(lhs) == getBeerCountry(rhs);
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
    static Cocktail mix( AlcoholDrink& ad, NonAlcoholDrink& nad)
    {
        if( nad == NonAlcoholDrink::LimeJuice && ad == AlcoholDrink::Gin )
        {
           return  Cocktail::Gimlet;
        }
        else if(  nad == NonAlcoholDrink::GrapefruitJuice && ad == AlcoholDrink::Gin )
        {
            return  Cocktail::Greyhount;
        }
        else if(nad == NonAlcoholDrink::SevenUp && ad == AlcoholDrink::Whiskey  )
        {
            return Cocktail::SevenPlusSeven;
        }
        else
        {
            return Cocktail::Oops;
        }
    }
};

std::function<Cocktail( AlcoholDrink&, NonAlcoholDrink& )> mixer {&MixingPolicy::mix};
