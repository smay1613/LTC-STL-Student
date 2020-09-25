#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand operator()()
    {
        if (currentIndex == static_cast<int>(BeerBrand::Max) - 1)
        {
            currentIndex = 0;
        }
        return beerStock[currentIndex++];
    }
private:
    int currentIndex = {0};
    std::array<BeerBrand, static_cast<int>(BeerBrand::Max) - 1> beerStock
    {
        BeerBrand::HoeGaarden,
        BeerBrand::Corona,
        BeerBrand::Carlsberg,
        BeerBrand::Bud,
        BeerBrand::ZlataPraha,
        BeerBrand::Leffe
    };
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand beer)
{
    return BeerBrand::Corona == beer || BeerBrand::HoeGaarden == beer;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */

auto sameCountry = [](const BeerBrand lhb, const BeerBrand rhb)
{
    return getBeerCountry(lhb) == getBeerCountry(rhb);
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
    static Cocktail mix(const AlcoholDrink alcoholicDrink, const NonAlcoholDrink nonAlcoholicDrink)
    {
        switch (alcoholicDrink){
            case AlcoholDrink::Gin:
            {
                if (NonAlcoholDrink::LimeJuice == nonAlcoholicDrink)
                {
                    return Cocktail::Gimlet;
                }
                if (NonAlcoholDrink::GrapefruitJuice == nonAlcoholicDrink)
                {
                    return Cocktail::Greyhount;
                }
            }
            break;
            case AlcoholDrink::Whiskey:
            {
                if (NonAlcoholDrink::SevenUp == nonAlcoholicDrink)
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
