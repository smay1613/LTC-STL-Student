#pragma once
#include "bar_serving.h"
#include <functional>
#include <iostream>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    size_t state {static_cast<size_t>(BeerBrand::None)};
    BeerBrand operator()(){
        if (static_cast<BeerBrand>(state) == BeerBrand::None||static_cast<BeerBrand>(state) == BeerBrand::Max)
        {
            state = static_cast<size_t>(BeerBrand::HoeGaarden);
        }        
        return static_cast<BeerBrand>(state++);
    }
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand bearBrand) 
{
   return (BeerBrand::Corona == bearBrand || BeerBrand::HoeGaarden == bearBrand);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand lhs, BeerBrand rhs)
{
    return getBeerCountry(lhs)==getBeerCountry(rhs);
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
    static Cocktail mix(AlcoholDrink lhs, NonAlcoholDrink rhs)
    {       
            if (AlcoholDrink::Gin == lhs && NonAlcoholDrink::LimeJuice == rhs)
            {
                return Cocktail::Gimlet;
            }
            else if (AlcoholDrink::Gin == lhs && NonAlcoholDrink::GrapefruitJuice == rhs)
            {
                return Cocktail::Greyhount;
            }         
            else if (AlcoholDrink::Whiskey == lhs && NonAlcoholDrink::SevenUp == rhs)
            {
                return Cocktail::SevenPlusSeven;
            }   
            else
            {
                return Cocktail::Oops;
            }      
        
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
