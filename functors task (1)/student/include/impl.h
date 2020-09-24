#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    size_t mLastBeerBrand = static_cast<size_t>( BeerBrand::None ) + 1;
    
    BeerBrand operator()();
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer( const BeerBrand );

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = []( const BeerBrand lhs, const BeerBrand rhs ) -> bool
{
    return getBeerCountry( lhs ) == getBeerCountry( rhs );
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
    static Cocktail mix( const AlcoholDrink& hard, const NonAlcoholDrink& soft );
};

std::function< Cocktail ( const AlcoholDrink& hard, const NonAlcoholDrink& soft ) > mixer {&MixingPolicy::mix};
