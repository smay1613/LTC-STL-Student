#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    size_t m_start = static_cast<size_t> (BeerBrand::HoeGaarden);
    size_t m_end = static_cast<size_t> (BeerBrand::Leffe);
    size_t m_next = m_start;

    BeerBrand operator()()
    {
        if(m_next > m_end) {
            m_next = m_start;
        }

        return static_cast<BeerBrand>(m_next++);
    }
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand brand)
{
    return (BeerBrand::Corona == brand) || (BeerBrand::HoeGaarden == brand);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand one, BeerBrand two)
{
    return getBeerCountry(one) == getBeerCountry(two);
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
    static Cocktail mix(const AlcoholDrink one, const NonAlcoholDrink two )
    {
        Cocktail result = Cocktail::Oops;

        switch (one) {
        case AlcoholDrink::Gin :
            if(NonAlcoholDrink::LimeJuice == two) {
                result = Cocktail::Gimlet;
            }
            if(NonAlcoholDrink::GrapefruitJuice == two) {
                result = Cocktail::Greyhount;
            }
            break;

        case AlcoholDrink::Whiskey :
            if(NonAlcoholDrink::SevenUp == two) {
                result = Cocktail::SevenPlusSeven;
            }
            break;
        default:
            break;
        }

        return result;
    }
};

std::function<Cocktail(const AlcoholDrink, const NonAlcoholDrink)> mixer {&MixingPolicy::mix};
