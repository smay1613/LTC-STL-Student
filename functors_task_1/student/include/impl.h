#pragma once
#include "bar_serving.h"
#include <functional>
#include <algorithm>
#include <vector>
#include <tuple>
#include <map>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand operator()();

private:
    size_t currentIndex{1};
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand& brand);

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand& lhs, const BeerBrand& rhs)
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
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink nonAlcohol);
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
