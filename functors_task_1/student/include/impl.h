#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand operator()()
    {
        constexpr size_t BEER_NUM = 6;
        constexpr wall_shelf<BEER_NUM> brands {
            BeerBrand::HoeGaarden,
            BeerBrand::Corona,
            BeerBrand::Carlsberg,
            BeerBrand::Bud,
            BeerBrand::ZlataPraha,
            BeerBrand::Leffe
        };

        if (index >= brands.size()) {
            index = 0;
        }
        return brands[index++];
    }

private:
    size_t index = 0;
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand brand)
{
    return brand == BeerBrand::Corona || brand == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand brand1, BeerBrand brand2)
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
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink soft)
    {
        switch (alcohol) {
            case AlcoholDrink::Gin: {
                switch (soft) {
                    case NonAlcoholDrink::LimeJuice: return Cocktail::Gimlet;
                    case NonAlcoholDrink::GrapefruitJuice: return Cocktail::Greyhount;
                    default: break;
                }
            } break;

            case AlcoholDrink::Whiskey: {
                switch (soft) {
                    case NonAlcoholDrink::SevenUp: return Cocktail::SevenPlusSeven;
                    default: break;
                }
            } break;

            default: break;
        }
        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
