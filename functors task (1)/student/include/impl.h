#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand operator()();
private:
    int32_t index = static_cast<int32_t>(BeerBrand::HoeGaarden); // 1
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand brand)
{
    return (brand == BeerBrand::Corona) || (brand == BeerBrand::HoeGaarden);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand brand1, BeerBrand brand2)
{
    return getBeerCountry(brand1) == getBeerCountry(brand2);
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
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink nonAlcohol)
    {
        Cocktail cocktail = Cocktail::Oops;

        if (alcohol == AlcoholDrink::Gin && nonAlcohol == NonAlcoholDrink::LimeJuice) {
            cocktail = Cocktail::Gimlet;
        }
        else if (alcohol == AlcoholDrink::Gin && nonAlcohol == NonAlcoholDrink::GrapefruitJuice) {
            cocktail = Cocktail::Greyhount;
        }
        else if (alcohol == AlcoholDrink::Whiskey && nonAlcohol == NonAlcoholDrink::SevenUp) {
            cocktail = Cocktail::SevenPlusSeven;
        }

        return cocktail;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
