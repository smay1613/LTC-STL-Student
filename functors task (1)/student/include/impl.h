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
        if (static_cast<int>(BeerBrand::Max) == current_beer + 1) {
            current_beer = 1;
        } else {
            ++current_beer;
        }
        return static_cast<BeerBrand>(current_beer);
    }
private:
    int current_beer = {0};
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beerBrand)
{
    return  BeerBrand::Corona == beerBrand || BeerBrand::HoeGaarden == beerBrand;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand b1, BeerBrand b2)
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
    static Cocktail mix(AlcoholDrink alcoholDrink, NonAlcoholDrink nonAlcoholDrink)
    {
        if (AlcoholDrink::Gin == alcoholDrink && NonAlcoholDrink::LimeJuice == nonAlcoholDrink) {
            return Cocktail::Gimlet;
        }
        else if (AlcoholDrink::Gin == alcoholDrink && NonAlcoholDrink::GrapefruitJuice == nonAlcoholDrink) {
            return Cocktail::Greyhount;
        }
        else if (AlcoholDrink::Whiskey == alcoholDrink && NonAlcoholDrink::SevenUp == nonAlcoholDrink) {
            return Cocktail::SevenPlusSeven;
        }
        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
