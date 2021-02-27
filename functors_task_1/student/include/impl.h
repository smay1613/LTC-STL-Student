#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerOrganizer() : m_first(static_cast<size_t>(BeerBrand::HoeGaarden))
      , m_last(static_cast<size_t>(BeerBrand::Max))
      , m_current(m_first) { }

    BeerBrand operator()() {
        if (m_current == m_last) {
            m_current = m_first;
        }

        return static_cast<BeerBrand>(m_current++);
    }

private:
    size_t m_first;
    size_t m_last;
    size_t m_current;
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
    static Cocktail mix(const AlcoholDrink ad, const NonAlcoholDrink nad)
    {
        if (ad == AlcoholDrink::Gin) {
            switch (nad) {
            case NonAlcoholDrink::LimeJuice      : return Cocktail::Gimlet;
            case NonAlcoholDrink::GrapefruitJuice: return Cocktail::Greyhount;
            }
        }

        if (ad == AlcoholDrink::Whiskey) {
            switch (nad) {
            case NonAlcoholDrink::SevenUp      : return Cocktail::SevenPlusSeven;
            }
        }

        return Cocktail::Oops;
    }
};

std::function<Cocktail(const AlcoholDrink, const NonAlcoholDrink)> mixer {&MixingPolicy::mix};
