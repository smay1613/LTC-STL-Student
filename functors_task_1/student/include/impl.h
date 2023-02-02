#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{  
    BeerBrand operator()(){
        if(currentIndex==static_cast<int>(BeerBrand::Leffe)){
            currentIndex=static_cast<int>(BeerBrand::None);
        }
        return static_cast<BeerBrand>(++currentIndex);
    }
    
    size_t currentIndex{static_cast<int>(BeerBrand::None)};
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand brand)
{ 
    return brand==BeerBrand::Corona || brand==BeerBrand::HoeGaarden;
   
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand lhs, const BeerBrand rhs)
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
    static Cocktail mix(const AlcoholDrink AlDrink,const NonAlcoholDrink NonAlDrink)
    {
        if(AlDrink==AlcoholDrink::Gin && NonAlDrink==NonAlcoholDrink::LimeJuice){
            return Cocktail::Gimlet;
        }

        if(AlDrink==AlcoholDrink::Gin && NonAlDrink==NonAlcoholDrink::GrapefruitJuice){
            return Cocktail::Greyhount;
        }
        if(AlDrink==AlcoholDrink::Whiskey && NonAlDrink==NonAlcoholDrink::SevenUp){
            return Cocktail::SevenPlusSeven;
        }

        return Cocktail::Oops;
    }
};

std::function<Cocktail(const AlcoholDrink,const NonAlcoholDrink)> mixer {&MixingPolicy::mix};
