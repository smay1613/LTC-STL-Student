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
        using convertedBeer = std::underlying_type<BeerBrand>::type;
        auto nextBeer ([this]() {
            return BeerBrand(static_cast<convertedBeer>(currentBear) + 1);
        });

        constexpr BeerBrand first = BeerBrand::HoeGaarden;
        constexpr BeerBrand last = BeerBrand::Leffe;

        if (currentBear == last) {
            currentBear = first;
        } else {
            currentBear = nextBeer();
        }
        return  currentBear;
    }
private:
    BeerBrand currentBear {BeerBrand::None};
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand beer)
{
    return (beer != BeerBrand::None) && (beer < BeerBrand::Carlsberg);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand lhs, const BeerBrand rhs)
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
    static Cocktail mix(const AlcoholDrink alcohol, const NonAlcoholDrink nonAlcohol)
    {
        auto drinkWithGin ([] (const NonAlcoholDrink nonAlcohol) {
            switch (nonAlcohol) {
            case NonAlcoholDrink::LimeJuice:
                return Cocktail::Gimlet;
            case NonAlcoholDrink::GrapefruitJuice:
                return Cocktail::Greyhount;
            default:
                return Cocktail::Oops;
            }
        });
        auto drinkWithWhiskey ([] (const NonAlcoholDrink nonAlcohol) {
            switch (nonAlcohol) {
            case NonAlcoholDrink::SevenUp:
                return Cocktail::SevenPlusSeven;
            default:
                return Cocktail::Oops;
            }
        });

        switch (alcohol) {
        case AlcoholDrink::Gin:
            return drinkWithGin(nonAlcohol);
        case AlcoholDrink::Whiskey:
            return drinkWithWhiskey(nonAlcohol);
        default:
            return Cocktail::Oops;
        }
    }
};

std::function<Cocktail(const AlcoholDrink, const NonAlcoholDrink)> mixer {&MixingPolicy::mix};
