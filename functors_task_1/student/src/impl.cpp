#include "impl.h"
#include <map>

BeerBrand BeerOrganizer::operator()() noexcept {
    if (m_beerNumber==m_max){
        m_beerNumber = m_min+1;
    }
    return static_cast<BeerBrand>(m_beerNumber++);
}

BeerOrganizer::BeerOrganizer() {
    static_assert(m_max-m_min>1, "You have only None and Max in enum!");
}

bool isExpensiveBeer(const BeerBrand brand) {
    return brand==BeerBrand::Corona || brand==BeerBrand::HoeGaarden;
}

Cocktail MixingPolicy::mix(const AlcoholDrink alcoholDrink, const NonAlcoholDrink nonAlcoholDrink) {
    using Ingredients = std::pair<AlcoholDrink, NonAlcoholDrink>;
    std::map<Ingredients, Cocktail> recipes = {
            {Ingredients{AlcoholDrink::Gin, NonAlcoholDrink::LimeJuice}, Cocktail::Gimlet},
            {Ingredients {AlcoholDrink::Gin, NonAlcoholDrink::GrapefruitJuice}, Cocktail::Greyhount},
            {Ingredients {AlcoholDrink::Whiskey, NonAlcoholDrink::SevenUp}, Cocktail::SevenPlusSeven}
            };
    const auto currentIngredients = std::make_pair(alcoholDrink, nonAlcoholDrink);
    const auto recipesIt = recipes.find(currentIngredients);
    if (recipesIt!=recipes.cend()){
        return recipesIt->second;
    }
    return Cocktail::Oops;
}
