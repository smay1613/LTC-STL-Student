#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand operator()() {
        if (currentIndex > toIndex) {
            currentIndex = fromIndex;
        }
        return static_cast<BeerBrand>(currentIndex++);
    }

private:
    int currentIndex = static_cast<int>(BeerBrand::HoeGaarden);
    int fromIndex = static_cast<int>(BeerBrand::HoeGaarden);
    int toIndex = static_cast<int>(BeerBrand::Leffe);
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand &beerBrand)
{
    return beerBrand == BeerBrand::Corona || beerBrand == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand &firstBeerBrand, const BeerBrand &secondBeerBrand)
{
    return getBeerCountry(firstBeerBrand) == getBeerCountry(secondBeerBrand);
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
    static Cocktail mix(const AlcoholDrink &alcoholDrink, const NonAlcoholDrink &nonAlcoholDrink)
    {
        if (alcoholDrink == AlcoholDrink::Gin) {
            if (nonAlcoholDrink == NonAlcoholDrink::LimeJuice) {
                return Cocktail::Gimlet;
            } else if (nonAlcoholDrink == NonAlcoholDrink::GrapefruitJuice) {
                 return Cocktail::Greyhount;
            }
        } else if (alcoholDrink == AlcoholDrink::Whiskey && nonAlcoholDrink == NonAlcoholDrink::SevenUp) {
            return Cocktail::SevenPlusSeven;
        }

        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
