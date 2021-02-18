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
        ++brandIndex;
        if (brandIndex == to)
        {
            brandIndex = from;
        }
        return static_cast<BeerBrand>(brandIndex);
    }

private:
    size_t brandIndex {static_cast<size_t>(BeerBrand::None)};

    static constexpr size_t from = static_cast<size_t>(BeerBrand::HoeGaarden);
    static constexpr size_t to = static_cast<size_t>(BeerBrand::Max);
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beer)
{
    if (beer == BeerBrand::Corona || beer == BeerBrand::HoeGaarden)
    {
        return true;
    }
    return false;
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
    static Cocktail mix(AlcoholDrink lhs, NonAlcoholDrink rhs)
    {
        switch (lhs) {
        case AlcoholDrink::Gin:
            switch (rhs) {
            case NonAlcoholDrink::LimeJuice:
                return Cocktail::Gimlet;
            case NonAlcoholDrink::GrapefruitJuice:
                return Cocktail::Greyhount;
            }
            break;
        case AlcoholDrink::Whiskey:
            switch (rhs) {
            case NonAlcoholDrink::SevenUp:
                return Cocktail::SevenPlusSeven;
            }
            break;
        }

        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
