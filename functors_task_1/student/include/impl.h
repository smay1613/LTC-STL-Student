#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
private:
    size_t currentIndex {1};

public:
    BeerBrand operator()() {
        if (currentIndex == static_cast<int>(BeerBrand::Max)) {
            currentIndex = 1;
        }
        return BeerBrand(currentIndex++);
    }
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beer)
{
    if (beer == BeerBrand::Corona || beer == BeerBrand::HoeGaarden) {
        return true;
    }
    return false;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand lhs, BeerBrand rhs)
{
    if (getBeerCountry(lhs) == getBeerCountry(rhs)) {
        return true;
    }
    return false;
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
        if (alcohol == AlcoholDrink::Gin && nonAlcohol == NonAlcoholDrink::LimeJuice) {
            return Cocktail::Gimlet;
        } else if (alcohol == AlcoholDrink::Gin && nonAlcohol == NonAlcoholDrink::GrapefruitJuice) {
            return Cocktail::Greyhount;
        } else if (alcohol == AlcoholDrink::Whiskey && nonAlcohol == NonAlcoholDrink::SevenUp) {
            return Cocktail::SevenPlusSeven;
        } else {
            return Cocktail::Oops;
        }
    }
};

std::function<Cocktail(AlcoholDrink alcohol, NonAlcoholDrink nonAlcohol)> mixer {&MixingPolicy::mix};
