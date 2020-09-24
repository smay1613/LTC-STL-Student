#include "impl.h"

BeerBrand BeerOrganizer::operator()()
{
    if ( mLastBeerBrand == static_cast<size_t>( BeerBrand::Max ) )
    {
        mLastBeerBrand = static_cast<size_t>( BeerBrand::None ) + 1;
    }

    return static_cast<BeerBrand>( mLastBeerBrand++ );
}

bool isExpensiveBeer( const BeerBrand brand )
{
    std::array<BeerBrand,2> expensiveOnes = { BeerBrand::Corona, BeerBrand::HoeGaarden };
    
    for ( const BeerBrand expensive : expensiveOnes )
    {
        if ( brand == expensive )
            return true;
    }

    return false;
}

Cocktail MixingPolicy::mix( const AlcoholDrink& hard, const NonAlcoholDrink& soft )
{
    if ( hard == AlcoholDrink::Gin     && soft == NonAlcoholDrink::GrapefruitJuice ) return Cocktail::Greyhount;
    if ( hard == AlcoholDrink::Gin     && soft == NonAlcoholDrink::LimeJuice )       return Cocktail::Gimlet;
    if ( hard == AlcoholDrink::Whiskey && soft == NonAlcoholDrink::SevenUp )         return Cocktail::SevenPlusSeven;

    return Cocktail::Oops;
}