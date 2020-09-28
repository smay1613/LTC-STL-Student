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
  size_t _current{static_cast<size_t>(BeerBrand::None)};

 public:
  BeerBrand operator()() {
    if (static_cast<size_t>(BeerBrand::Max) - 1 == _current) {
      _current = static_cast<size_t>(BeerBrand::None);
    }
    return static_cast<BeerBrand>(++_current);
  };
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
    switch (drink1) {
      case AlcoholDrink::Gin:
        switch (drink2) {
          case NonAlcoholDrink::LimeJuice:
            cocktail = Cocktail::Gimlet;
            break;
          case NonAlcoholDrink::GrapefruitJuice:
            cocktail = Cocktail::Greyhount;
            break;
          default:
            cocktail = Cocktail::Oops;
            break;
        }
        break;
      case AlcoholDrink::Whiskey:
        switch (drink2) {
          case NonAlcoholDrink::SevenUp:
            cocktail = Cocktail::SevenPlusSeven;
            break;
          default:
            cocktail = Cocktail::Oops;
            break;
        }
        break;
      default:
        cocktail = Cocktail::Oops;
        break;
    }
    return cocktail;
  }
};

std::function<Cocktail(const AlcoholDrink, const NonAlcoholDrink)> mixer{
    &MixingPolicy::mix};
