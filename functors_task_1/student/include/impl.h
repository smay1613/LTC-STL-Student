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
            m_currentIndex = static_cast<size_t>(BeerBrand::None);
        }

        return static_cast<BeerBrand>(++m_currentIndex);
    }

private:
    size_t m_currentIndex{static_cast<size_t>(BeerBrand::None)};
    size_t m_maxIndex{static_cast<size_t>(BeerBrand::Max)};
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand brand)
{
    return brand == BeerBrand::Corona || brand == BeerBrand::HoeGaarden;
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
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink nonAlcohol)
    {
        if (alcohol == AlcoholDrink::Gin && nonAlcohol == NonAlcoholDrink::LimeJuice) {
            return Cocktail::Gimlet;
        }
        if (alcohol == AlcoholDrink::Gin && nonAlcohol == NonAlcoholDrink::GrapefruitJuice) {
            return Cocktail::Greyhount;
        }
        if (alcohol == AlcoholDrink::Whiskey && nonAlcohol == NonAlcoholDrink::SevenUp) {
            return Cocktail::SevenPlusSeven;
        }
        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
