#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    size_t firstBeer = static_cast<int>(BeerBrand::HoeGaarden);
    size_t lastBeer = static_cast<int>(BeerBrand::Leffe);
    size_t beer = firstBeer;

    BeerBrand operator()()
    {
       size_t currentBeer = beer;
       if(beer < lastBeer)
       {
           beer ++;
       }
       else
       {
           beer = firstBeer;
       }

       return static_cast<BeerBrand>(currentBeer);
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
    return (brand == BeerBrand::HoeGaarden || brand == BeerBrand::Corona);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand lhr , BeerBrand rhs)
{
    return getBeerCountry(lhr) == getBeerCountry(rhs);
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
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink noAlcohol)
    {
        Cocktail currentCoctail = Cocktail::Oops;
        if(alcohol == AlcoholDrink::Gin)
        {
            if(noAlcohol == NonAlcoholDrink::LimeJuice)
            {
                currentCoctail = Cocktail::Gimlet;
            }
            else if(noAlcohol == NonAlcoholDrink::GrapefruitJuice)
            {
                currentCoctail = Cocktail::Greyhount;
            }
        }
        else if(alcohol == AlcoholDrink::Whiskey && noAlcohol == NonAlcoholDrink::SevenUp)
        {
            currentCoctail = Cocktail::SevenPlusSeven;
        }

        return currentCoctail;
    }
};

std::function<Cocktail(AlcoholDrink,NonAlcoholDrink)> mixer {&MixingPolicy::mix};
