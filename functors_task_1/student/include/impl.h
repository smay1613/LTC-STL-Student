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
        if(m_currentIndex == m_end)
            m_currentIndex = m_begin;

        return static_cast<BeerBrand>(m_currentIndex++);
    }

private:
    const size_t m_begin = static_cast<size_t>(BeerBrand::HoeGaarden);
    const size_t m_end = static_cast<size_t>(BeerBrand::Max);
    size_t m_currentIndex = m_begin;

};
/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand beer)
{
    return beer == BeerBrand::Corona || beer == BeerBrand::HoeGaarden;
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
    static Cocktail mix(const AlcoholDrink alchohol, const NonAlcoholDrink nonAlcohol)
    {
        switch(alchohol)
        {
        case AlcoholDrink::Gin:
            switch(nonAlcohol)
            {
            case NonAlcoholDrink::LimeJuice:
                return Cocktail::Gimlet;
            case NonAlcoholDrink::GrapefruitJuice:
                return Cocktail::Greyhount;
            default:
                return Cocktail::Oops;
            }

            break;
        case AlcoholDrink::Whiskey:
            return nonAlcohol == NonAlcoholDrink::SevenUp ? Cocktail::SevenPlusSeven : Cocktail::Oops;
        default:
            return Cocktail::Oops;
        }
    }
};

std::function<Cocktail(const AlcoholDrink alchohol, const NonAlcoholDrink nonAlcohol)> mixer {&MixingPolicy::mix};
