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
    int next_beer = static_cast<int>(BeerBrand::HoeGaarden);

public:
    BeerBrand operator()() {
        if (next_beer == static_cast<int>(BeerBrand::Max))
            next_beer = static_cast<int>(BeerBrand::HoeGaarden);
        return static_cast<BeerBrand>(next_beer++);
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
    return beer == BeerBrand::HoeGaarden || beer == BeerBrand::Corona;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand beer1, const BeerBrand beer2)
{
    return getBeerCountry(beer1) == getBeerCountry(beer2);
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
    static Cocktail mix(AlcoholDrink alcDrink, NonAlcoholDrink nonAlcDrink)
    {
        switch(alcDrink) {
            case AlcoholDrink::Gin:
                switch(nonAlcDrink) {
                    case NonAlcoholDrink::LimeJuice:
                        return Cocktail::Gimlet;
                    case NonAlcoholDrink::GrapefruitJuice:
                        return Cocktail::Greyhount;
                    default:
                        break;
                }
                break;
            case AlcoholDrink::Whiskey:
                switch(nonAlcDrink) {
                    case NonAlcoholDrink::SevenUp:
                        return Cocktail::SevenPlusSeven;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
