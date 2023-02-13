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
    int beer_brand = static_cast<int>(BeerBrand::HoeGaarden);

public:
    BeerBrand operator()() {
        if (beer_brand == static_cast<int>(BeerBrand::Max))
            beer_brand = static_cast<int>(BeerBrand::HoeGaarden);
        return static_cast<BeerBrand>(beer_brand++);
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
auto sameCountry = [](const BeerBrand brand1, const BeerBrand brand2)
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
    static Cocktail mix(AlcoholDrink alcDrink, NonAlcoholDrink nonAlcDrink)
    {
        static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink nonAlcohol)
            {
                if(alcohol == AlcoholDrink::Gin && nonAlcohol == NonAlcoholDrink::LimeJuice) return Cocktail::Gimlet;
                else if(alcohol == AlcoholDrink::Gin && nonAlcohol == NonAlcoholDrink::GrapefruitJuice) return Cocktail::Greyhount;
                else if(alcohol == AlcoholDrink::Whiskey && nonAlcohol == NonAlcoholDrink::SevenUp) return Cocktail::SevenPlusSeven;
                else return Cocktail::Oops;

            }
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
