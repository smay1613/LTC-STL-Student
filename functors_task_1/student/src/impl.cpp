#include "impl.h"

BeerBrand BeerOrganizer::operator()() {
    if (static_cast<size_t>(BeerBrand::Max) == currentIndex)
        currentIndex = 1;

    return static_cast<BeerBrand>(currentIndex++);
}

bool isExpensiveBeer(const BeerBrand& brand)
{
    std::vector<BeerBrand> expensive{BeerBrand::HoeGaarden, BeerBrand::Corona};

    return std::find(expensive.begin(), expensive.end(), brand) != std::end(expensive);
}

Cocktail MixingPolicy::mix(AlcoholDrink alcohol, NonAlcoholDrink nonAlcohol)
{
    using Recipe = std::tuple<AlcoholDrink, NonAlcoholDrink>;
    using Ingredients = std::pair<AlcoholDrink, NonAlcoholDrink>;

    std::map<Recipe, Cocktail> cookbook{{Ingredients(AlcoholDrink::Gin, NonAlcoholDrink::LimeJuice), Cocktail::Gimlet},
                                        {Ingredients(AlcoholDrink::Gin, NonAlcoholDrink::GrapefruitJuice), Cocktail::Greyhount},
                                        {Ingredients(AlcoholDrink::Whiskey, NonAlcoholDrink::SevenUp), Cocktail::SevenPlusSeven}};

    auto cocktail = cookbook.find(Ingredients{alcohol, nonAlcohol});

    return cocktail != std::end(cookbook) ? cocktail->second : Cocktail::Oops;
}
