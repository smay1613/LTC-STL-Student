#pragma once
#include <array>

/** @warning: do not change the values of enum */
enum class BeerBrand
{
    None = 0,
    HoeGaarden,
    Corona,
    Carlsberg,
    Bud,
    ZlataPraha,
    Leffe,
    Max = 7
};

enum class Country
{
    Unknown,
    Ukraine,
    Mexico,
    Belgium
};

enum class NonAlcoholDrink
{
    LimeJuice,
    OrangeJuice,
    GrapefruitJuice,
    Fanta,
    SevenUp
};

enum class AlcoholDrink
{
    Gin,
    Whiskey,
    Wine,
    Beer
};

enum class Cocktail
{
    Oops = 0,

    Gimlet,
    Greyhount,
    SevenPlusSeven,

    MAX = SevenPlusSeven
};

template<size_t N>
using wall_shelf = std::array<BeerBrand, N>;

template<class DrinkType>
using shots_stand = std::array<DrinkType, 8>;

template<class BeerOrderGenerator, size_t N>
void composeWallShelf(wall_shelf<N>& shelf, BeerOrderGenerator nextBeerByOrder)
{
    for (auto& space : shelf)
    {
        space = nextBeerByOrder();
    }
}

template<class RemoveByCriteriaPredicate, size_t N>
void removeBeerByCriteria(wall_shelf<N>& shelf, RemoveByCriteriaPredicate shouldBeRemoved)
{
    for (auto& space : shelf)
    {
        if (shouldBeRemoved(space))
        {
            space = BeerBrand::None;
        }
    }
}

template<class BeerComparator, size_t N>
bool haveSameProperty(wall_shelf<N>& shelf_lhs, BeerComparator comparator)
{
    for(size_t i = 0; i < N - 1; i++)
    {
        if (!comparator(shelf_lhs[i], shelf_lhs[i + 1]))
        {
            return false;
        }
    }
    return true;
}

template<class MixerTransformator>
shots_stand<Cocktail> mix(shots_stand<AlcoholDrink>& shelf_lhs, shots_stand<NonAlcoholDrink>& shelf_rhs, MixerTransformator mix)
{
    shots_stand<Cocktail> coctails;
    constexpr auto N = coctails.size();
    for(size_t i = 0; i < N; i++)
    {
        coctails[i] = mix(shelf_lhs[i], shelf_rhs[i]);
    }
    return coctails;
}

Country getBeerCountry(BeerBrand brand)
{
    switch (brand)
    {
        case BeerBrand::Corona:
        {
            return Country::Mexico;
        }
        case BeerBrand::Leffe:
        case BeerBrand::HoeGaarden:
        {
            return Country::Belgium;
        }
        case BeerBrand::ZlataPraha:
        case BeerBrand::Carlsberg:
        case BeerBrand::Bud:
        {
            return Country::Ukraine;
        }
        case BeerBrand::Max:
        case BeerBrand::None:
        default:
        {
            return Country::Unknown;
        }
    }
}
