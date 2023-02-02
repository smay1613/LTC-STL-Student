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
        if(currentIndex==static_cast<int>(BeerBrand::Max)){
            currentIndex=static_cast<int>(BeerBrand::HoeGaarden);
        }
        return static_cast<BeerBrand>(currentIndex++);
    }
    
    size_t currentIndex{static_cast<int>(BeerBrand::HoeGaarden)};
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
        switch (AlDrink)
        {
            case AlcoholDrink::Gin:
            {
                switch (NonAlDrink)
                {
                    case NonAlcoholDrink::LimeJuice:
                        return Cocktail::Gimlet;

                    case NonAlcoholDrink::GrapefruitJuice:
                        return Cocktail::Greyhount;

                    default:
                        break;
                }
            }
            break;

            case AlcoholDrink::Whiskey:
            {
                switch (NonAlDrink)
                {
                    case NonAlcoholDrink::SevenUp:
                        return Cocktail::SevenPlusSeven;

                    default:
                        break;
                }
            }
            break;

            default:
                break;
        }

        return Cocktail::Oops;
    }
};

std::function<Cocktail(const AlcoholDrink,const NonAlcoholDrink)> mixer {&MixingPolicy::mix};
