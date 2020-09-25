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
        size_t currentBeerIndex = static_cast<size_t>(BeerBrand::HoeGaarden);

    public:
        BeerBrand operator()();
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beerBrand)
{
    return beerBrand == BeerBrand::Corona || beerBrand == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand firstBeerBrand, BeerBrand secondBeerBrand)
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
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink nonAlcohol)
    {
        Cocktail cocktail = Cocktail::Oops;
        switch (alcohol)
        {
        case AlcoholDrink::Gin:
            if (nonAlcohol == NonAlcoholDrink::LimeJuice)
            {
                cocktail = Cocktail::Gimlet;
            }
            else if (nonAlcohol == NonAlcoholDrink::GrapefruitJuice)
            {
                cocktail = Cocktail::Greyhount;
            }
            break;
        case AlcoholDrink::Whiskey:
            if (nonAlcohol == NonAlcoholDrink::SevenUp)
            {
                cocktail = Cocktail::SevenPlusSeven;
            }
            break;
        }
        return cocktail;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
