#pragma once
#include "bar_serving.h"
#include <functional>
#include <vector>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    private:
    int index=1;

    public:
    BeerBrand operator()()
    {
        if(index == (int)BeerBrand::Max)
        {
            index = 1;
        }

        return BeerBrand++;
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
    return beer == BeerBrand::Corona || beer == BeerBrand::HoeGaarden ? true : false;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand beer1, BeerBrand beer2)
{
    return (int)getBeerCountry(beer1) == (int)getBeerCountry(beer2);
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
    static Cocktail mix(AlcoholDrink alcoholDrink, NonAlcoholDrink nonAlcoholDrink)
    {
        if(alcoholDrink == AlcoholDrink::Gin && nonAlcoholDrink == NonAlcoholDrink::LimeJuice)
            return Cocktail::Gimlet;
        if(alcoholDrink == AlcoholDrink::Gin && nonAlcoholDrink == NonAlcoholDrink::GrapefruitJuice)
            return Cocktail::Greyhount;
        if(alcoholDrink == AlcoholDrink::Whiskey && nonAlcoholDrink == NonAlcoholDrink::SevenUp)
            return Cocktail::SevenPlusSeven;
        else   
            return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
