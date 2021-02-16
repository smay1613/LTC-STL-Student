#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerOrganizer();
    size_t m_number;
    static const auto m_max = static_cast<size_t>(BeerBrand::Max);
    static const auto m_min = static_cast<size_t>(BeerBrand::None);
    BeerBrand operator()() noexcept;
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
auto sameCountry = [](const BeerBrand first, const BeerBrand second)
{
    return getBeerCountry(first)==getBeerCountry(second);
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
    static Cocktail mix(const AlcoholDrink alcoholDrink, const NonAlcoholDrink nonAlcoholDrink);
};

std::function<Cocktail(const AlcoholDrink, const NonAlcoholDrink)> mixer {&MixingPolicy::mix};
