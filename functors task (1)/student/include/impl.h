#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
  size_t current_index {static_cast<size_t>(BeerBrand::HoeGaarden)};

  BeerBrand operator() (){
    if(current_index == static_cast<size_t>(BeerBrand::Max))
      {
        current_index = static_cast<size_t>(BeerBrand::HoeGaarden);
      }
    return static_cast<BeerBrand>(current_index++);
  }
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
auto sameCountry = [](BeerBrand lhv, BeerBrand rhv)
{
  return getBeerCountry(lhv) == getBeerCountry(rhv);
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
    static Cocktail mix(AlcoholDrink alco, NonAlcoholDrink nonAlco)
    {
      switch(alco){
        case AlcoholDrink::Gin:
          {
            if(nonAlco == NonAlcoholDrink::LimeJuice)
              {
                return Cocktail::Gimlet;
              }
            if(nonAlco == NonAlcoholDrink::GrapefruitJuice)
              {
                return Cocktail::Greyhount;
              }
            break;
          }
        case AlcoholDrink::Whiskey:
          {
            if(nonAlco == NonAlcoholDrink::SevenUp)
              {
                return Cocktail::SevenPlusSeven;
              }
          }
       }
       return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
