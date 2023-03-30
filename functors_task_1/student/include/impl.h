#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    int first_value = static_cast<int>(BeerBrand::HoeGaarden);
    int last_value = static_cast<int>(BeerBrand::Max);
    int next = first_value;

    BeerBrand operator()() {
        if (next == last_value) {
            next = first_value;
        }
        return static_cast<BeerBrand>(next++);
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
    if (beer == BeerBrand::Corona || beer == BeerBrand::HoeGaarden)
        return true;
    else
        return false;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand brand, BeerBrand beer)
{
    if (getBeerCountry(beer) == getBeerCountry(brand))
        return true;
    else
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
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink nonalcohol)
    {
        switch (alcohol) {
        case AlcoholDrink::Gin:
            switch (nonalcohol) {
            case NonAlcoholDrink::LimeJuice:
                return Cocktail::Gimlet;
                break;
            case NonAlcoholDrink::GrapefruitJuice:
                return Cocktail::Greyhount;
                break;
            default:
                return Cocktail::Oops;
                break;
            }
            break;
        case AlcoholDrink::Whiskey:
            if (nonalcohol == NonAlcoholDrink::SevenUp)
                return Cocktail::SevenPlusSeven;
            else
                return Cocktail::Oops;
            break;
        default:
            return Cocktail::Oops;
            break;
        }
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer{&MixingPolicy::mix};
