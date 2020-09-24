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

        static BeerBrand beer = BeerBrand::Leffe;

        switch(beer){
        case BeerBrand::HoeGaarden: beer = BeerBrand::Corona; break;
        case BeerBrand::Corona:     beer = BeerBrand::Carlsberg; break;
        case BeerBrand::Carlsberg:  beer = BeerBrand::Bud; break;
        case BeerBrand::Bud:        beer = BeerBrand::ZlataPraha; break;
        case BeerBrand::ZlataPraha: beer = BeerBrand::Leffe; break;
        case BeerBrand::Leffe:      beer = BeerBrand::HoeGaarden; break;
        default: break;
        }
        return beer;
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
    return (BeerBrand::Corona == beer) || (BeerBrand::HoeGaarden == beer);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand& beer_first, const BeerBrand& beer_second)
{
    return (getBeerCountry(beer_first) == getBeerCountry(beer_second));
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
    static Cocktail mix(const AlcoholDrink& drink_alc, const NonAlcoholDrink& drink_nalc )
    {
        Cocktail result = Cocktail::Oops;
        switch (drink_alc) {
        case AlcoholDrink::Gin:
            if(NonAlcoholDrink::LimeJuice == drink_nalc){
                result = Cocktail::Gimlet;
            } else if(NonAlcoholDrink::GrapefruitJuice == drink_nalc) {
                result = Cocktail::Greyhount;
            }
            break;
        case AlcoholDrink::Whiskey:
            if(NonAlcoholDrink::SevenUp == drink_nalc){
                result = Cocktail::SevenPlusSeven;
            }
            break;
        default:
            break;
        }
        return result;
    }
};

std::function<Cocktail(const AlcoholDrink&,const NonAlcoholDrink&)> mixer {&MixingPolicy::mix};
