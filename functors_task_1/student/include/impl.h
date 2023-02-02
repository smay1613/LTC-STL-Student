#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
	int brand = static_cast<int>(BeerBrand::None);
	BeerBrand operator()() {
		if (brand == static_cast<int>(BeerBrand::Leffe))
			brand = static_cast<int>(BeerBrand::None);
		return static_cast<BeerBrand>(++brand);
	}
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beer)
{
	return (beer == BeerBrand::Corona || beer == BeerBrand::HoeGaarden );
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand &c1,const BeerBrand &c2)
{
	return getBeerCountry(c1) == getBeerCountry(c2);
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
    static Cocktail mix(AlcoholDrink bev1, NonAlcoholDrink bev2)
    {
		switch (bev1)
		{
		case AlcoholDrink::Gin:
			if (bev2 == NonAlcoholDrink::LimeJuice) return Cocktail::Gimlet;
			else if (bev2 == NonAlcoholDrink::GrapefruitJuice) return Cocktail::Greyhount;
			else return Cocktail::Oops;
		case AlcoholDrink::Whiskey:
			if (bev2 == NonAlcoholDrink::SevenUp) return Cocktail::SevenPlusSeven;
		default:
			return Cocktail::Oops;
		}
	}
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
