#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
  size_t current_index {0};
  std::array<BeerBrand, 8> beer_arr {
        BeerBrand::HoeGaarden,
        BeerBrand::Corona,
        BeerBrand::Carlsberg,
        BeerBrand::Bud,
        BeerBrand::ZlataPraha,
        BeerBrand::Leffe
  };


  BeerBrand operator() (){
    if(current_index == beer_arr.size())
      {
        current_index = 0;
      }
    return beer_arr[current_index++];
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
  switch(brand){
      case BeerBrand::Corona:
      {
        return true;
      }
      case BeerBrand::HoeGaarden:
      {
        return true;
      }
      default:
      {
        return false;
      }
  }
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
      if(alco == AlcoholDrink::Gin && nonAlco == NonAlcoholDrink::LimeJuice)
        {
          return Cocktail::Gimlet;
        }
      else if(alco == AlcoholDrink::Gin && nonAlco == NonAlcoholDrink::GrapefruitJuice)
        {
          return Cocktail::Greyhount;
        }
      else if(alco == AlcoholDrink::Whiskey && nonAlco == NonAlcoholDrink::SevenUp)
        {
          return Cocktail::SevenPlusSeven;
        }
      else{
          return Cocktail::Oops;
        }
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
