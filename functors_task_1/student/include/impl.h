#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerOrganizer(): currentBear{BeerBrand::None} {}

    BeerBrand operator()() {
        if (currentBear == BeerBrand::Leffe) {
            currentBear = BeerBrand::HoeGaarden;
        } else {
            currentBear = BeerBrand(static_cast<std::underlying_type<BeerBrand>::type>(currentBear) + 1);
        }
        return  currentBear;
    }
private:
    BeerBrand currentBear;
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand beer)
{
    return (beer != BeerBrand::None) && (beer < BeerBrand::Carlsberg);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand lhs, const BeerBrand rhs)
{
    return getBeerCountry(lhs) == getBeerCountry(rhs);
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
    static Cocktail mix(const AlcoholDrink alcohol, const NonAlcoholDrink nonAlcohol)
    {
        if (alcohol == AlcoholDrink::Gin) {
            if (nonAlcohol == NonAlcoholDrink::LimeJuice) {
                return Cocktail::Gimlet;
            } else if (nonAlcohol == NonAlcoholDrink::GrapefruitJuice) {
                return Cocktail::Greyhount;
            }
        } else if (alcohol == AlcoholDrink::Whiskey && nonAlcohol == NonAlcoholDrink::SevenUp) {
            return Cocktail::SevenPlusSeven;
        }
        return  Cocktail::Oops;
    }
};

std::function<Cocktail(const AlcoholDrink, const NonAlcoholDrink)> mixer {&MixingPolicy::mix};
