#pragma once
#include <functional>
#include "bar_serving.h"

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe ->
 * HoeGaarden...
 */
struct BeerOrganizer {
 private:
  size_t _current;

 public:
  BeerOrganizer() : _current(0){};
  BeerBrand operator()();
};

/**
 * @todo Implement unary predicate function that will determine if beer is
 * expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand brand) {
  return BeerBrand::Corona == brand || BeerBrand::HoeGaarden == brand;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand brand1, const BeerBrand brand2) {
  return getBeerCountry(brand1) == getBeerCountry(brand2);
};

struct MixingPolicy {
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
  static Cocktail mix(const AlcoholDrink drink1, const NonAlcoholDrink drink2) {
    auto cocktail = Cocktail::Oops;
    if (AlcoholDrink::Gin == drink1 && NonAlcoholDrink::LimeJuice == drink2) {
      cocktail = Cocktail::Gimlet;
    } else if (AlcoholDrink::Gin == drink1 &&
               NonAlcoholDrink::GrapefruitJuice == drink2) {
      cocktail = Cocktail::Greyhount;
    } else if (AlcoholDrink::Whiskey == drink1 &&
               NonAlcoholDrink::SevenUp == drink2) {
      cocktail = Cocktail::SevenPlusSeven;
    }
    return cocktail;
  }
};

std::function<Cocktail(const AlcoholDrink, const NonAlcoholDrink)> mixer{
    &MixingPolicy::mix};
