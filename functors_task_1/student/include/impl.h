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
        int nextIndex = getNextIndex();
        static constexpr int from = static_cast<int>(BeerBrand::HoeGaarden);
        static constexpr int to = static_cast<int>(BeerBrand::Leffe);
        state = (from <= nextIndex && to >= nextIndex) ? static_cast<BeerBrand>(nextIndex) : BeerBrand::HoeGaarden;
        return state;
    }
private:
    int getNextIndex() const
    {
        return (static_cast<int>(state) + 1) % static_cast<int>(BeerBrand::Max);
    }
    BeerBrand state = BeerBrand::None;
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
auto sameCountry = [](const BeerBrand brand1, const BeerBrand brand2)
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
        switch (alcDrink)
        {
            case AlcoholDrink::Gin:
                switch(nonAlcDrink)
                {
                    case NonAlcoholDrink::LimeJuice:
                    {
                        return Cocktail::Gimlet;
                    }
                    case NonAlcoholDrink::GrapefruitJuice:
                    {
                        return Cocktail::Greyhount;
                    }
                    default:
                    {
                        return Cocktail::Oops;
                    }
                }
            case AlcoholDrink::Whiskey:
                switch (nonAlcDrink)
                {
                    case NonAlcoholDrink::SevenUp:
                    {
                        return Cocktail::SevenPlusSeven;
                    }
                    default:
                    {
                        return Cocktail::Oops;
                    }
                }
            default:
            {
                return Cocktail::Oops;
            }
        }
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
