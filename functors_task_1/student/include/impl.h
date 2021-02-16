#pragma once
#include "bar_serving.h"
#include <functional>
#include <type_traits>


/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand operator()();

private:
    using BaseType = std::underlying_type<BeerBrand>::type;
    const BaseType m_begin = static_cast<BaseType>(BeerBrand::None) + 1;
    const BaseType m_end = static_cast<BaseType>(BeerBrand::Max);
    BaseType m_nextBeer = m_begin;
};



/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand brand);

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand lhd, BeerBrand rhd)
{
    return getBeerCountry(lhd) == getBeerCountry(rhd);
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
    static Cocktail mix(const AlcoholDrink lhd, const NonAlcoholDrink rhd);
};

std::function<Cocktail(const AlcoholDrink, const NonAlcoholDrink)> mixer {&MixingPolicy::mix};
