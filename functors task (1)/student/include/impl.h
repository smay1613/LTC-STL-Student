#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
	BeerBrand operator() () {
		static int band = 0;
		band < 6 && band > 0 ? band++ : band =  1;
		return static_cast<BeerBrand>(band);
	}
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beerBand)
{
	return (beerBand == BeerBrand::HoeGaarden) || (beerBand == BeerBrand::Corona);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand brand1, BeerBrand brand2)
{
	return getBeerCountry(brand1) == getBeerCountry(brand2);
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
		Cocktail result = Cocktail::Oops;
		if (alco == AlcoholDrink::Gin && nonAlco == NonAlcoholDrink::LimeJuice)
			result = Cocktail::Gimlet;
		if (alco == AlcoholDrink::Gin && nonAlco == NonAlcoholDrink::GrapefruitJuice)
			result = Cocktail::Greyhount;
		if (alco == AlcoholDrink::Whiskey && nonAlco == NonAlcoholDrink::SevenUp)
			result = Cocktail::SevenPlusSeven;
		return result;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
