#pragma once
#include <functional>
#include "bar_serving.h"

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe ->
 * HoeGaarden...
 */
struct BeerOrganizer {
 public:
  BeerBrand operator()() {
    BeerBrand bb = static_cast<BeerBrand>(index);
    ++index;
    if (index == 7) {
      index = 1;
    }

    return bb;
  }

 private:
  int index = 1;
};

/**
 * @todo Implement unary predicate function that will determine if beer is
 * expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand const& bb) {
  bool result = false;
  switch (bb) {
    case BeerBrand::Corona:
    case BeerBrand::HoeGaarden:
      result = true;
      break;
    default:
      result = false;
  }

  return result;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand const& bb1, BeerBrand const& bb2) {
  return getBeerCountry(bb1) == getBeerCountry(bb2);
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
  static Cocktail mix(AlcoholDrink ad, NonAlcoholDrink nad) {
    if (AlcoholDrink::Gin == ad && NonAlcoholDrink::LimeJuice == nad) {
      return Cocktail::Gimlet;
    } else if (AlcoholDrink::Gin == ad &&
               NonAlcoholDrink::GrapefruitJuice == nad) {
      return Cocktail::Greyhount;
    } else if (AlcoholDrink::Whiskey == ad && NonAlcoholDrink::SevenUp == nad) {
      return Cocktail::SevenPlusSeven;
    } else
      return Cocktail::Oops;
  }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer =
    &MixingPolicy::mix;
