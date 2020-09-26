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
        beerBrandType = static_cast<BeerBrand>(static_cast <size_t> (beerBrandType) +1); 
        if (beerBrandType == BeerBrand::Max)
        {
            beerBrandType = BeerBrand::HoeGaarden;
        }    
           
        return beerBrandType;
    }

private:

 BeerBrand beerBrandType {BeerBrand::None};
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
    static Cocktail mix(const AlcoholDrink alcoholDrink, const NonAlcoholDrink nonAlcoholDrink)
    {
        switch (alcoholDrink){
            case AlcoholDrink::Gin:
            {
                if (NonAlcoholDrink::LimeJuice == nonAlcoholDrink)
                {
                    return Cocktail::Gimlet;
                }
                if (NonAlcoholDrink::GrapefruitJuice == nonAlcoholDrink)
                {
                    return Cocktail::Greyhount;
                }
            }
            break;
            case AlcoholDrink::Whiskey:
            {
                if (NonAlcoholDrink::SevenUp == nonAlcoholDrink)
                {
                    return Cocktail::SevenPlusSeven;
                }
            }
            break;
            default:
            break;
        }
        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
