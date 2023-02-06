#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand beer = BeerBrand::None;

    BeerBrand operator()()
    {
        beer = static_cast<BeerBrand>(static_cast<int>(beer) + 1) ;
        if(beer == BeerBrand::Max)beer = BeerBrand::HoeGaarden;
        return beer;
    }
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beer)
{
    if(beer == BeerBrand::Corona || beer == BeerBrand::HoeGaarden) return true;
    return false;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand beer1,BeerBrand beer2)
{
    if(getBeerCountry(beer1)  == getBeerCountry(beer2)) return true;
    return false;
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
    static Cocktail mix(AlcoholDrink alcohol , NonAlcoholDrink nonalcohol)
    {
        if(alcohol == AlcoholDrink::Gin && nonalcohol == NonAlcoholDrink::LimeJuice )
            return Cocktail::Gimlet;
        if(alcohol == AlcoholDrink::Gin && nonalcohol == NonAlcoholDrink::GrapefruitJuice )
            return Cocktail::Greyhount;
        if(alcohol == AlcoholDrink::Whiskey && nonalcohol == NonAlcoholDrink::SevenUp )
            return Cocktail::SevenPlusSeven;
        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink,NonAlcoholDrink)> mixer {&MixingPolicy::mix};
