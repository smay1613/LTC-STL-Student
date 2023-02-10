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
    BeerBrand beer;

    public:
    BeerBrand operator()()
    {
        beer = (BeerBrand)((int)beer+1);

        if(beer == BeerBrand::Max)
        {
            beer = (BeerBrand)((int)BeerBrand::None+1);
        }

        return beer;
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
        if(alcoholDrink == AlcoholDrink::Gin && nonAlcoholDrink == NonAlcoholDrink::LimeJuice)
            return Cocktail::Gimlet;
        if(alcoholDrink == AlcoholDrink::Gin && nonAlcoholDrink == NonAlcoholDrink::GrapefruitJuice)
            return Cocktail::Greyhount;
        if(alcoholDrink == AlcoholDrink::Whiskey && nonAlcoholDrink == NonAlcoholDrink::SevenUp)
            return Cocktail::SevenPlusSeven;
        else   
            return Cocktail::Oops;

        switch (alcoholDrink)
        {
            case AlcoholDrink::Gin:
            {
                switch (nonAlcoholDrink)
                {
                    case NonAlcoholDrink::LimeJuice:
                        return Cocktail::Gimlet;
                    
                    case NonAlcoholDrink::GrapefruitJuice:
                        return Cocktail::Greyhount;
                    
                    default:
                        return Cocktail::Oops;
                }
            }
                
            case AlcoholDrink::Whiskey:
                switch (nonAlcoholDrink)
                {
                    case NonAlcoholDrink::SevenUp:
                        return Cocktail::SevenPlusSeven;
                    
                    default:
                        return Cocktail::Oops;
                }
            default:
                return Cocktail::Oops;
            }
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
