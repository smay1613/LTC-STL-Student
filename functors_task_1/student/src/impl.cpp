#include "impl.h"

BeerBrand BeerOrganizer::operator()() {
    if (static_cast<size_t>(BeerBrand::Max) == currentIndex)
        currentIndex = static_cast<size_t>(BeerBrand::HoeGaarden);

    return static_cast<BeerBrand>(currentIndex++);
}

bool isExpensiveBeer(BeerBrand brand)
{
    switch(brand)
    {
    case BeerBrand::HoeGaarden:
    case BeerBrand::Corona:
        return true;
    default:
        return false;
    }
}

Cocktail MixingPolicy::mix(AlcoholDrink alcohol, NonAlcoholDrink nonAlcohol)
{
    using Recipe = std::pair<AlcoholDrink, NonAlcoholDrink>;

    struct hashPair
    {
        size_t operator()(const Recipe& recipe) const
        {
            size_t first = static_cast<size_t>(recipe.first);
            size_t second = static_cast<size_t>(recipe.second);

            size_t cantorPairing = (first + second) * (first + second + 1) / 2 + second;
            return cantorPairing;
        }
    };

    static const std::unordered_map<Recipe, Cocktail, hashPair> cookbook{{Recipe(AlcoholDrink::Gin, NonAlcoholDrink::LimeJuice), Cocktail::Gimlet},
                                                                         {Recipe(AlcoholDrink::Gin, NonAlcoholDrink::GrapefruitJuice), Cocktail::Greyhount},
                                                                         {Recipe(AlcoholDrink::Whiskey, NonAlcoholDrink::SevenUp), Cocktail::SevenPlusSeven}};

    auto cocktail = cookbook.find(Recipe{alcohol, nonAlcohol});

    return cocktail != std::end(cookbook) ? cocktail->second : Cocktail::Oops;
}
