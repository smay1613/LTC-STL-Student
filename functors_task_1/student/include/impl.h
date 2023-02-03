#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    int initial_value = static_cast<int>(BeerBrand::HoeGaarden);
    int next = initial_value;
    int last_value = static_cast<int>(BeerBrand::Max);
    
    BeerBrand operator()(){
        if(next == last_value){
            next = initial_value;
        }
       return static_cast<BeerBrand>(next++);
    }
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand beer)
{
    return beer == BeerBrand::Corona || beer == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand brand, BeerBrand beer)
{
    return getBeerCountry(beer) == getBeerCountry(brand);
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
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink juice)
    {
        switch(alcohol){
            case AlcoholDrink::Gin:
                switch(juice){
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
                return (juice == NonAlcoholDrink::SevenUp)?Cocktail::SevenPlusSeven:Cocktail::Oops;
                break;
            default:
                return Cocktail::Oops;
                break;
        }
    }
};

std::function<Cocktail(AlcoholDrink,NonAlcoholDrink)> mixer {&MixingPolicy::mix};
