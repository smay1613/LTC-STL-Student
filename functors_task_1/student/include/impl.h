#pragma once
#include "bar_serving.h"
#include <functional>
#include <iostream>
#include <map>

using namespace std;

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */

struct BeerOrganizer
{
    void operator()(){
        for (int i = 0; i < static_cast<int>(BeerBrand::Max); ++i){
            BeerBrand B = static_cast<BeerBrand>(i);
            switch (B)
            {
            case BeerBrand::HoeGaarden:
                cout << "HoeGaarden -> "; 
                break;
            
            case BeerBrand::Corona:
                cout << "Corona -> "; 
                break;            
            
            case BeerBrand::Carlsberg:
                cout << "Carlsberg -> "; 
                break;            
            
            case BeerBrand::Bud:
                cout << "Bud -> "; 
                break;            
            
            case BeerBrand::ZlataPraha:
                cout << "ZlataPraha -> "; 
                break;
            
            case BeerBrand::Leffe:
                cout << "Leffe -> "; 
                break;                

            }
        }
      }

};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand B)
{
    return B == BeerBrand::Corona || B == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand B1, BeerBrand B2)
{
    return getBeerCountry(B1) == getBeerCountry(B2);
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
    static Cocktail mix(AlcoholDrink D1, NonAlcoholDrink D2)
    {
        static const std::map<std::pair<AlcoholDrink, NonAlcoholDrink>, Cocktail> Cookbook = {
            {{AlcoholDrink::Gin, NonAlcoholDrink::LimeJuice},Cocktail::Gimlet},
            {{AlcoholDrink::Gin,NonAlcoholDrink::GrapefruitJuice},Cocktail::Greyhount},
            {{AlcoholDrink::Whiskey,NonAlcoholDrink::SevenUp},Cocktail::SevenPlusSeven}
        };

        auto i = Cookbook.find({D1,D2});
        return (i != Cookbook.end()) ? i->second : Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
