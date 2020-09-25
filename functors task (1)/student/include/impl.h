#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
     size_t currentIndex {1};
     BeerBrand beer;
     BeerBrand operator()()
     {
       if(static_cast<BeerBrand>(currentIndex) == BeerBrand::Max){
           currentIndex = 1;
       }
       beer = static_cast<BeerBrand>(currentIndex++);
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
    if( (beer == BeerBrand::Corona) || (beer == BeerBrand::HoeGaarden)){
        return true;
    }
    else{
        return false;
    }
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand beer1, BeerBrand beer2)
{
    return getBeerCountry(beer1) == getBeerCountry(beer2);
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
        if ((alcoholDrink == AlcoholDrink::Gin) && (nonAlcoholDrink == NonAlcoholDrink::LimeJuice))
        {
            return Cocktail::Gimlet;
        }
        else if ((alcoholDrink == AlcoholDrink::Gin) && (nonAlcoholDrink == NonAlcoholDrink::GrapefruitJuice)) {
            return Cocktail::Greyhount;
        }
        else if ((alcoholDrink == AlcoholDrink::Whiskey) && (nonAlcoholDrink == NonAlcoholDrink::SevenUp)) {
            return Cocktail::SevenPlusSeven;
        }
        else {
             return Cocktail::Oops;
        }
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
