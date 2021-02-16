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
    {
    }
    BeerBrand operator()()
    {
        auto result = BeerBrand::None;
        do
        {
            if(0 == mBrands.size())
            {
                break;
            }
            result = *(std::begin(mBrands) + mBrandIndex);
            ++mBrandIndex;
            if(mBrands.size() <= mBrandIndex)
            {
                mBrandIndex = 0;
            }
        }while(false);
        return result;
    }
private:
    typedef std::array<BeerBrand, (int)(BeerBrand::Max) - 1> BeerBrandsType;
    BeerBrandsType mBrands = {BeerBrand::HoeGaarden, BeerBrand::Corona, BeerBrand::Carlsberg, BeerBrand::Bud, BeerBrand::ZlataPraha, BeerBrand::Leffe};
    uint mBrandIndex{0};
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand brand)
{
    return (brand == BeerBrand::HoeGaarden ||
            brand == BeerBrand::Corona) ? true : false;
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
        Cocktail result = Cocktail::Oops;
        if(AlcoholDrink::Gin == lhs && NonAlcoholDrink::LimeJuice == rhs)
        {
            result = Cocktail::Gimlet;
        }
        else if(AlcoholDrink::Gin == lhs && NonAlcoholDrink::GrapefruitJuice == rhs)
        {
            result = Cocktail::Greyhount;
        }
        else if(AlcoholDrink::Whiskey == lhs && NonAlcoholDrink::SevenUp == rhs)
        {
            result = Cocktail::SevenPlusSeven;
        }
        return result;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
