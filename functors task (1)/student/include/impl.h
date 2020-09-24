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
        if (currentIndex == (int)BeerBrand::Max - 1)
        {
            currentIndex = 0;
        }
        return beerStock[currentIndex++];
    }
private:
    int currentIndex = {0};
    std::array<BeerBrand, (int)BeerBrand::Max> beerStock
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
    static Cocktail mix(const AlcoholDrink adrink, const NonAlcoholDrink nadrink)
    {
        if (AlcoholDrink::Gin == adrink && NonAlcoholDrink::LimeJuice == nadrink)
        {
            return Cocktail::Gimlet;
        }
        if (AlcoholDrink::Gin == adrink && NonAlcoholDrink::GrapefruitJuice == nadrink)
        {
            return Cocktail::Greyhount;
        }
        if (AlcoholDrink::Whiskey == adrink && NonAlcoholDrink::SevenUp == nadrink)
        {
            return Cocktail::SevenPlusSeven;
        }
        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
