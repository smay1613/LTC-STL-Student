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
        if(mBrandNumber == static_cast<uint>(BeerBrand::Max))
        {
            mBrandNumber = mFirstValidBrandNumber;
        }
        auto result = static_cast<BeerBrand>(mBrandNumber);
        mBrandNumber++;
        return result;
    }
private:
    const uint mFirstValidBrandNumber{static_cast<uint>(BeerBrand::None) + 1};
    uint mBrandNumber{mFirstValidBrandNumber};
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand brand)
{
    return (brand == BeerBrand::HoeGaarden ||
            brand == BeerBrand::Corona);
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
    static Cocktail mix(const AlcoholDrink alcohol, const NonAlcoholDrink nonalcohol)
    {
        Cocktail result = Cocktail::Oops;
        switch(alcohol)
        {
            case AlcoholDrink::Gin:
                switch(nonalcohol)
                {
                    case NonAlcoholDrink::LimeJuice:
                        return Cocktail::Gimlet;
                    case NonAlcoholDrink::GrapefruitJuice:
                        return Cocktail::Greyhount;
                    default:
                        return Cocktail::Oops;
                }
            case AlcoholDrink::Whiskey:
                switch(nonalcohol)
                {
                    case NonAlcoholDrink::SevenUp:
                        return Cocktail::SevenPlusSeven;
                    default:
                        return Cocktail::Oops;
                }
            default:
                return Cocktail::Oops;
        }
        return result;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
