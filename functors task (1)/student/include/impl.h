#pragma once
#include "bar_serving.h"
#include <functional>
#include <map>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand operator()();

    private:
    size_t counter = static_cast<size_t>(BeerBrand::None);
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand& brand)
{
    return brand == BeerBrand::Corona || brand == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand& lbrand, const BeerBrand& rbrand)
{
    return getBeerCountry(lbrand) == getBeerCountry(rbrand);
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
    static Cocktail mix(const AlcoholDrink& lDrink, const NonAlcoholDrink& rDrink)
    {
        Cocktail cocktail = Cocktail::Oops;
        auto iter = bar.find(std::make_pair(lDrink, rDrink));
        if(bar.end() != iter)
        {
            cocktail = iter->second;
        }
        return cocktail;
    }
    private:
    static std::map <std::pair<AlcoholDrink, NonAlcoholDrink>, Cocktail> bar;
};

std::function<Cocktail(const AlcoholDrink&, const NonAlcoholDrink&)> mixer {&MixingPolicy::mix};