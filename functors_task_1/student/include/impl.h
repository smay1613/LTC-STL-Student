#pragma once
#include "bar_serving.h"
#include <functional>
#include <set>
#include <map>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
private:
    int m_currentIndex = 0;
public:
    BeerBrand operator()() {
        m_currentIndex = m_currentIndex == static_cast<int>(BeerBrand::Leffe) ? 1 : ++m_currentIndex;
        return BeerBrand(m_currentIndex);
    }
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand& beer)
{
    std::set<BeerBrand> expensiveBeers = {BeerBrand::Corona, BeerBrand::HoeGaarden};
    return expensiveBeers.find(beer) != expensiveBeers.end();
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand& first, const BeerBrand& second)
{
    return getBeerCountry(first) == getBeerCountry(second);
};

using Coctails = std::map<std::pair<AlcoholDrink, NonAlcoholDrink>, Cocktail>;

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
private:
    static Coctails m_coctails;
public:
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink nonAlcohol)
    {
        return m_coctails.find({alcohol, nonAlcohol}) != m_coctails.end() ? m_coctails[{alcohol, nonAlcohol}]
                                                                          : Cocktail::Oops;
    }
};

Coctails MixingPolicy::m_coctails= {{{AlcoholDrink::Gin, NonAlcoholDrink::LimeJuice}, Cocktail::Gimlet},
                                    {{AlcoholDrink::Gin, NonAlcoholDrink::GrapefruitJuice}, Cocktail::Greyhount},
                                    {{AlcoholDrink::Whiskey, NonAlcoholDrink::SevenUp}, Cocktail::SevenPlusSeven}};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
