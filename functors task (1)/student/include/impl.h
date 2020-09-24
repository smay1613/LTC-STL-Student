#pragma once

#include "bar_serving.h"

#include <functional>
#include <map>
#include <utility>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    constexpr int beerBrandBegin() const
    {
        return static_cast<int>(BeerBrand::None) + 1;
    }

    constexpr int beerBrandEnd() const
    {
        return static_cast<int>(BeerBrand::Max);
    }

    BeerBrand operator()()
    {
        if (nextBeerBrand == beerBrandEnd())
        {
            nextBeerBrand = beerBrandBegin();
        }
        return static_cast<BeerBrand>(nextBeerBrand++);
    }

    int nextBeerBrand = beerBrandBegin();
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beerBrand)
{
    return beerBrand == BeerBrand::Corona || beerBrand == BeerBrand::HoeGaarden;
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
    static Cocktail mix(AlcoholDrink alcoholDrink, NonAlcoholDrink nonAlcoholDrink)
    {
        static const std::map<std::pair<AlcoholDrink, NonAlcoholDrink>, Cocktail> kCocktailsMap =
        {
            { { AlcoholDrink::Gin    , NonAlcoholDrink::LimeJuice       }, Cocktail::Gimlet         },
            { { AlcoholDrink::Gin    , NonAlcoholDrink::GrapefruitJuice }, Cocktail::Greyhount      },
            { { AlcoholDrink::Whiskey, NonAlcoholDrink::SevenUp         }, Cocktail::SevenPlusSeven },
        };

        const auto foundCocktail = kCocktailsMap.find({ alcoholDrink, nonAlcoholDrink });

        return foundCocktail != kCocktailsMap.end() ? foundCocktail->second : Cocktail::Oops;
    }
};

std::function<decltype(MixingPolicy::mix)> mixer {&MixingPolicy::mix};
