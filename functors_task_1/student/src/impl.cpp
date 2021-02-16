#include "impl.h"
#include <array>
#include <algorithm>

BeerBrand BeerOrganizer::operator()() noexcept {
    if (m_number==m_max){
        m_number = m_min+1;
    }
    return static_cast<BeerBrand>(m_number++);
}

BeerOrganizer::BeerOrganizer():m_number(m_min+1) {
    static_assert(m_max-m_min>1, "You have only None and Max in enum!");
}

bool isExpensiveBeer(const BeerBrand brand) {
    constexpr static std::array<BeerBrand, 2> expensiveBeers =
            {BeerBrand::Corona, BeerBrand::HoeGaarden};
    return std::find(expensiveBeers.cbegin(), expensiveBeers.cend(), brand)!=expensiveBeers.cend();
}

Cocktail MixingPolicy::mix(const AlcoholDrink alcoholDrink, const NonAlcoholDrink nonAlcoholDrink) {
    using Ingredients = std::pair<AlcoholDrink, NonAlcoholDrink>;
    using Recipe = std::pair<Ingredients , Cocktail>;
    constexpr static std::array<Recipe , 3> recipes = {
            Recipe {Ingredients{AlcoholDrink::Gin, NonAlcoholDrink::LimeJuice}, Cocktail::Gimlet},
            Recipe {Ingredients {AlcoholDrink::Gin, NonAlcoholDrink::GrapefruitJuice}, Cocktail::Greyhount},
            Recipe {Ingredients {AlcoholDrink::Whiskey, NonAlcoholDrink::SevenUp}, Cocktail::SevenPlusSeven}
            };
    const auto currentIngredients = std::make_pair(alcoholDrink, nonAlcoholDrink);
    for (const auto& item : recipes){
        if (currentIngredients == item.first){
            return item.second;
        }
    }
    return Cocktail::Oops;
}
