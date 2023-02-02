#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    int brandId = static_cast<int>(BeerBrand::HoeGaarden);

    BeerBrand operator()()
    {
        if (brandId == static_cast<int>(BeerBrand::Max))
            brandId = static_cast<int>(BeerBrand::HoeGaarden);

        return static_cast<BeerBrand>(brandId++);
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
    return brand == BeerBrand::Corona || brand == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand b1, BeerBrand b2)
{
    return getBeerCountry(b1) == getBeerCountry(b2);
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
    static Cocktail mix(AlcoholDrink alcDrink, NonAlcoholDrink nonAlcDrink)
    {
        if (alcDrink == AlcoholDrink::Gin && nonAlcDrink == NonAlcoholDrink::LimeJuice)
            return Cocktail::Gimlet;
        else if (alcDrink == AlcoholDrink::Gin && nonAlcDrink == NonAlcoholDrink::GrapefruitJuice)
            return Cocktail::Greyhount;
        else if (alcDrink == AlcoholDrink::Whiskey && nonAlcDrink == NonAlcoholDrink::SevenUp)
            return Cocktail::SevenPlusSeven;
        
        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
