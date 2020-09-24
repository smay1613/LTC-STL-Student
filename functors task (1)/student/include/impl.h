#pragma once
#include "bar_serving.h"
#include <functional>
#include <vector>
#include <map>


/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand operator()()
    {
        if(mCurrentBrand == OrderedBrands.end())
        {
            mCurrentBrand = OrderedBrands.begin();
        }
        return *(mCurrentBrand++);
    }
private:
    static const std::vector<BeerBrand> OrderedBrands;
    std::vector<BeerBrand>::const_iterator mCurrentBrand = OrderedBrands.begin();
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beer)
{
    return beer == BeerBrand::Corona || beer == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand beer1, BeerBrand beer2)
{
    return getBeerCountry(beer1) == getBeerCountry(beer2);
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
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink non_alcohol)
    {
        static const std::map<std::pair<AlcoholDrink, NonAlcoholDrink>, Cocktail> recipes = {
            { {AlcoholDrink::Gin,     NonAlcoholDrink::LimeJuice},       Cocktail::Gimlet },
            { {AlcoholDrink::Gin,     NonAlcoholDrink::GrapefruitJuice}, Cocktail::Greyhount },
            { {AlcoholDrink::Whiskey, NonAlcoholDrink::SevenUp},         Cocktail::SevenPlusSeven }
        };
        auto recipe = recipes.find(std::make_pair(alcohol, non_alcohol));
        return (recipe == recipes.end()) ? Cocktail::Oops : recipe->second;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
