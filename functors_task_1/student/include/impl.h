#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand current_beer = BeerBrand::None;

    BeerBrand operator()()
    {
        current_beer = static_cast<BeerBrand>(static_cast<int>(current_beer) + 1) ;

        if(current_beer == BeerBrand::Max)
        {
            current_beer = BeerBrand::HoeGaarden;
        }

        return current_beer;
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
    return (beer == BeerBrand::Corona || beer == BeerBrand::HoeGaarden);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand beer1,BeerBrand beer2)
{
    return (getBeerCountry(beer1)  == getBeerCountry(beer2));
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
        switch(alcohol)
        {
            case AlcoholDrink::Gin:
                switch(nonalcohol)
                {
                    case NonAlcoholDrink::LimeJuice:
                        return Cocktail::Gimlet;
                        break;
                    case NonAlcoholDrink::GrapefruitJuice:
                        return Cocktail::Greyhount;
                        break;
                    default:
                        return Cocktail::Oops;
                        break;
                }
                break;
            case AlcoholDrink::Whiskey:
                switch(nonalcohol)
                {
                    case NonAlcoholDrink::SevenUp:
                        return Cocktail::SevenPlusSeven;
                        break;
                    default:
                        return Cocktail::Oops;
                        break;
                    }
                    break;
            default:
                return Cocktail::Oops;
                break;
        }
    }
};

std::function<Cocktail(AlcoholDrink,NonAlcoholDrink)> mixer {&MixingPolicy::mix};
