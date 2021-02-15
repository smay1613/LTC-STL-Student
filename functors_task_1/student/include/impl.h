#pragma once
#include "bar_serving.h"
#include <functional>
using namespace std;
/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand m_it=BeerBrand::None;
public:
    BeerBrand operator ()(){
        m_it = (BeerBrand)(std::underlying_type<BeerBrand>::type(m_it) + 1);
        if(BeerBrand::Max==m_it){
            m_it=BeerBrand::HoeGaarden;
        }
        return m_it;
    };
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand beerBrand)
{
    return (BeerBrand::Corona==beerBrand || BeerBrand::HoeGaarden==beerBrand);
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand lhs,const BeerBrand rhs)
{
    const auto lCountry= getBeerCountry(lhs);
    const auto rCountry= getBeerCountry(rhs);
    if(Country::Unknown==lCountry){
        return false;
    }
    return lCountry==rCountry;
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
    static Cocktail mix(const AlcoholDrink alcohol,const NonAlcoholDrink nonAlcohol)
    {
        auto result=Cocktail::Oops;
        if(AlcoholDrink::Gin==alcohol){
            if(NonAlcoholDrink::LimeJuice==nonAlcohol){
                result=Cocktail::Gimlet;
            }else if(NonAlcoholDrink::GrapefruitJuice==nonAlcohol){
                result=Cocktail::Greyhount;
            }
        }else if(AlcoholDrink::Whiskey==alcohol){
            if(NonAlcoholDrink::SevenUp==nonAlcohol){
                result=Cocktail::SevenPlusSeven;
            }
        }
        return  result;
    }
};

std::function<Cocktail(const AlcoholDrink ,const NonAlcoholDrink )> mixer {&MixingPolicy::mix};
