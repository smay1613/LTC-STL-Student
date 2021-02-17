#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerOrganizer()
        : state{BeerBrand::None}
    {}
    BeerBrand operator()()
    {
        int nextIndex = getNextIndex();
        state = (0 == nextIndex) ? BeerBrand::HoeGaarden : static_cast<BeerBrand>(nextIndex);
        return state;
    }
private:
    int getNextIndex()
    {
        return (static_cast<int>(state) + 1) % static_cast<int>(BeerBrand::Max);
    }
    BeerBrand state;
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand brand)
{
    switch (brand)
    {
        case BeerBrand::Corona:
        case BeerBrand::HoeGaarden:
        {
            return true;
        }
        case BeerBrand::Leffe:
        case BeerBrand::ZlataPraha:
        case BeerBrand::Carlsberg:
        case BeerBrand::Bud:
        case BeerBrand::Max:
        case BeerBrand::None:
        default:
        {
            return false;
        }
    }
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
    static Cocktail mix(AlcoholDrink alcDrink, NonAlcoholDrink nonAlcDrink)
    {
        if(alcDrink == AlcoholDrink::Gin && nonAlcDrink == NonAlcoholDrink::LimeJuice)
        {
            return Cocktail::Gimlet;
        }
        else if (alcDrink == AlcoholDrink::Gin && nonAlcDrink == NonAlcoholDrink::GrapefruitJuice)
        {
            return Cocktail::Greyhount;
        }
        else if (alcDrink == AlcoholDrink::Whiskey && nonAlcDrink == NonAlcoholDrink::SevenUp)
        {
            return Cocktail::SevenPlusSeven;
        }
        else
        {
            return Cocktail::Oops;
        }
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
