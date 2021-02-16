#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand operator()() {
        if (m_currentIndex == m_maxIndex - 1) {
            m_currentIndex = m_minIndex;
        }

        return static_cast<BeerBrand>(++m_currentIndex);
    }

private:
    size_t m_currentIndex{static_cast<size_t>(BeerBrand::None)};
    size_t m_minIndex{static_cast<size_t>(BeerBrand::None)};
    size_t m_maxIndex{static_cast<size_t>(BeerBrand::Max)};
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand brand)
{
    return brand == BeerBrand::Corona || brand == BeerBrand::HoeGaarden;
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
    static Cocktail mix(const AlcoholDrink alcohol, const NonAlcoholDrink nonAlcohol)
    {
        switch (alcohol) {
            case AlcoholDrink::Gin:

            switch (nonAlcohol) {
                case NonAlcoholDrink::LimeJuice:
                    return Cocktail::Gimlet;
                case NonAlcoholDrink::GrapefruitJuice:
                    return Cocktail::Greyhount;
                default:
                    return Cocktail::Oops;
            }

            case AlcoholDrink::Whiskey:
                return nonAlcohol == NonAlcoholDrink::SevenUp ? Cocktail::SevenPlusSeven : Cocktail::Oops;
            default:
                return Cocktail::Oops;
        }
    }
};

std::function<Cocktail(const AlcoholDrink, const NonAlcoholDrink)> mixer {&MixingPolicy::mix};
