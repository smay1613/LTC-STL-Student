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
bool isExpensiveBeer(const BeerBrand brand)
{
    return brand == BeerBrand::Corona || brand == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand b1, const BeerBrand b2)
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
    static Cocktail mix(const AlcoholDrink alcDrink, const NonAlcoholDrink nonAlcDrink)
    {
        switch (alcDrink)
        {
            case AlcoholDrink::Gin:
            {
                switch (nonAlcDrink)
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
                switch (nonAlcDrink)
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

std::function<Cocktail(const AlcoholDrink, const NonAlcoholDrink)> mixer {&MixingPolicy::mix};
