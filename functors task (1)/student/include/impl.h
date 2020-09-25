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
    size_t currentBeerBrand = static_cast<size_t>(BeerBrand::None);
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand beerBrand);

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand beerBrand1, BeerBrand beerBrand2)
{
    return getBeerCountry(beerBrand1) == getBeerCountry(beerBrand2);
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
        if (alcoholDrink == AlcoholDrink::Gin && nonAlcoholDrink == NonAlcoholDrink::LimeJuice)
            return Cocktail::Gimlet;
        if (alcoholDrink == AlcoholDrink::Gin && nonAlcoholDrink == NonAlcoholDrink::GrapefruitJuice)
            return Cocktail::Greyhount;
        if (alcoholDrink == AlcoholDrink::Whiskey && nonAlcoholDrink == NonAlcoholDrink::SevenUp)
            return Cocktail::SevenPlusSeven;
        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};

