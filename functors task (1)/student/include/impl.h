#pragma once
#include <cstdint>
#include <functional>
#include <map>
#include <utility>

#include "bar_serving.h"

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe ->
 * HoeGaarden...
 */
struct BeerOrganizer {
  // we can always be sure that generated beerBrand will be strictly between
  // None and Max exclusive
  BeerOrganizer() : m_beer{BeerBrand::None} {}

  BeerBrand operator()() {
    m_beer = static_cast<BeerBrand>(static_cast<uint>(m_beer) + 1);
    if (m_beer == BeerBrand::Max) {
      m_beer = static_cast<BeerBrand>(static_cast<uint>(BeerBrand::None) + 1);
    }
    return m_beer;
  }

 private:
  BeerBrand m_beer;
};

/**
 * @todo Implement unary predicate function that will determine if beer is
 * expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beer) {
  return (beer == BeerBrand::Corona) || (beer == BeerBrand::HoeGaarden);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand lhs, BeerBrand rhs) {
  return getBeerCountry(lhs) == getBeerCountry(rhs);
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

  static std::map<std::pair<AlcoholDrink, NonAlcoholDrink>, Cocktail>
      cocktailsRecipes;

  static Cocktail mix(AlcoholDrink ad, NonAlcoholDrink nad) {
    if (cocktailsRecipes.count({ad, nad}) > 0) {
      return cocktailsRecipes[{ad, nad}];
    }

    return Cocktail::Oops;
  }
};

std::map<std::pair<AlcoholDrink, NonAlcoholDrink>, Cocktail>
    MixingPolicy::cocktailsRecipes{
        {{AlcoholDrink::Gin, NonAlcoholDrink::LimeJuice}, Cocktail::Gimlet},
        {{AlcoholDrink::Gin, NonAlcoholDrink::GrapefruitJuice}, Cocktail::Greyhount},
        {{AlcoholDrink::Whiskey, NonAlcoholDrink::SevenUp}, Cocktail::SevenPlusSeven}};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer{
    &MixingPolicy::mix};
