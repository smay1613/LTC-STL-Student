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
        if (++mCurrentBrandIndex > mTo) {
            mCurrentBrandIndex = mFrom;
        }
        return static_cast<BeerBrand>(mCurrentBrandIndex);
    }

private:
    int mCurrentBrandIndex = static_cast<int>(BeerBrand::None);
    static const int mFrom = static_cast<int>(BeerBrand::HoeGaarden);
    static const int mTo = static_cast<int>(BeerBrand::Leffe);
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beerBrand)
{
    return beerBrand == BeerBrand::Corona
               || beerBrand == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand lhs, BeerBrand rhs)
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
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink nonAlcohol)
    {
        switch (alcohol) {
        case AlcoholDrink::Gin:
            if (nonAlcohol == NonAlcoholDrink::LimeJuice)
            {
                return  Cocktail::Gimlet;
            }
            if (nonAlcohol == NonAlcoholDrink::GrapefruitJuice)
            {
                return Cocktail::Greyhount;
            }
            break;
        case AlcoholDrink::Whiskey:
            if (nonAlcohol == NonAlcoholDrink::SevenUp)
            {
                return Cocktail::SevenPlusSeven;
            }
            break;
        }
     return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
