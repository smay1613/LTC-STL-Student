#include "maintest.h"

static_assert (IsOrderedAndConsistent<
                       BeerBrand::None,
                       BeerBrand::HoeGaarden,
                       BeerBrand::Corona,
                       BeerBrand::Carlsberg,
                       BeerBrand::Bud,
                       BeerBrand::ZlataPraha,
                       BeerBrand::Leffe,
                       BeerBrand::Max>::value,
               "Enum values must be ordered and not changed!");

TEST_F(Generator, AllEntriesAreValid)
{
    wall_shelf<20> shelf;
    composeWallShelf(shelf, BeerOrganizer {});

    auto contains = [&](const BeerBrand brand)
    {
        return std::find(shelf.begin(), shelf.end(), brand)
               != shelf.end();
    };
    EXPECT_FALSE(contains(BeerBrand::None));
    EXPECT_FALSE(contains(BeerBrand::Max));
}

TEST_F(Generator, FullFit)
{
    constexpr size_t expectedPartsCount = 3;
    wall_shelf<expectedPartsCount * 6> shelf;
    composeWallShelf(shelf, BeerOrganizer {});

    EXPECT_EQ(countShelfParts(shelf),
              expectedPartsCount);
}

TEST_F(Generator, SemiFit)
{
    constexpr size_t expectedPartsCount = 2;
    constexpr size_t nonFullPartSize = 3;
    wall_shelf<expectedPartsCount * 6 + nonFullPartSize> shelf;
    composeWallShelf(shelf, BeerOrganizer {});

    EXPECT_EQ(countShelfParts(shelf),
              expectedPartsCount);

    EXPECT_TRUE(std::equal(std::prev(shelf.end(), nonFullPartSize),
                           shelf.end(),
                           expectedShelfPart.begin(),
                           std::next(expectedShelfPart.begin(), nonFullPartSize)));
}

TEST_F(Predicate, AllRemoved)
{
    wall_shelf<6> shelf;

    for (const auto& expensiveBeerType : {BeerBrand::Corona, BeerBrand::HoeGaarden})
    {
        shelf.fill(expensiveBeerType);
        removeBeerByCriteria(shelf, isExpensiveBeer);
        EXPECT_TRUE(std::all_of(shelf.begin(), shelf.end(),
                                isEqualTo(BeerBrand::None)));
    }
}

TEST_F(Predicate, NoRemoved)
{
    wall_shelf<6> shelf;

    for (const auto& nonExpensiveBeerType : {BeerBrand::Bud, BeerBrand::Leffe,
                                             BeerBrand::Carlsberg, BeerBrand::ZlataPraha})
    {
        shelf.fill(nonExpensiveBeerType);
        removeBeerByCriteria(shelf, isExpensiveBeer);
        EXPECT_TRUE(std::none_of(shelf.begin(), shelf.end(),
                                 isEqualTo(BeerBrand::None)));
    }
}

TEST_F(Predicate, DefaultShelf)
{
    wall_shelf<6> shelf;
    composeWallShelf(shelf, BeerOrganizer {});

    removeBeerByCriteria(shelf, isExpensiveBeer);

    EXPECT_EQ(std::count(shelf.begin(), shelf.end(), BeerBrand::None),
              2);
}

TEST(Comparator, DifferentCountries)
{
    wall_shelf<6> shelf;
    composeWallShelf(shelf, BeerOrganizer {});

    EXPECT_FALSE(haveSameProperty(shelf, sameCountry));
}

TEST(Comparator, SameBeer)
{
    wall_shelf<6> shelf;
    shelf.fill(BeerBrand::Leffe);

    EXPECT_TRUE(haveSameProperty(shelf, sameCountry));
}

TEST(Comparator, NoBeer)
{
    wall_shelf<6> shelf;
    shelf.fill(BeerBrand::None);

    EXPECT_TRUE(haveSameProperty(shelf, sameCountry));
}

TEST(Comparator, SameCountryDifferentBeer_Belgium)
{
    wall_shelf<6> shelf;
    auto partitionPointIt = shelf.begin() + shelf.size() / 2;
    std::fill(shelf.begin(), partitionPointIt, BeerBrand::Leffe);
    std::fill(partitionPointIt, shelf.end(), BeerBrand::HoeGaarden);

    EXPECT_TRUE(haveSameProperty(shelf, sameCountry));
}

TEST(Comparator, SameCountryDifferentBeer_Ukraine)
{
    wall_shelf<6> shelf;

    auto partitionPointIt = shelf.begin() + shelf.size() / 2;

    std::fill(shelf.begin(), partitionPointIt, BeerBrand::Bud);
    std::fill(partitionPointIt, shelf.end(), BeerBrand::Carlsberg);
    shelf.front() = BeerBrand::ZlataPraha;

    EXPECT_TRUE(haveSameProperty(shelf, sameCountry));
}

TEST(Transform, AllCombinations)
{
    shots_stand<AlcoholDrink> alcohol;
    shots_stand<NonAlcoholDrink> nonAlcohol;

    size_t success_count {0};
    for (const auto& drink1 : {AlcoholDrink::Gin, AlcoholDrink::Beer,
                               AlcoholDrink::Wine, AlcoholDrink::Whiskey})
    {
        alcohol.fill(drink1);
        for (const auto& drink2 : {NonAlcoholDrink::Fanta,
                                   NonAlcoholDrink::SevenUp, NonAlcoholDrink::LimeJuice,
                                   NonAlcoholDrink::OrangeJuice, NonAlcoholDrink::GrapefruitJuice})
        {
            nonAlcohol.fill(drink2);
            shots_stand<Cocktail> mixed {mix(alcohol, nonAlcohol, mixer)};
            if (std::count(mixed.begin(), mixed.end(), Cocktail::Oops) == 0)
            {
                ++success_count;
            }
        }
    }

    EXPECT_EQ(success_count, static_cast<size_t>(Cocktail::MAX));
}

TEST(Transform, MixTable)
{
    shots_stand<AlcoholDrink> alcohol {AlcoholDrink::Gin, AlcoholDrink::Gin, AlcoholDrink::Gin,
                                       AlcoholDrink::Beer, AlcoholDrink::Wine,
                                       AlcoholDrink::Whiskey, AlcoholDrink::Wine, AlcoholDrink::Whiskey};

    shots_stand<NonAlcoholDrink> nonAlcohol {NonAlcoholDrink::LimeJuice, NonAlcoholDrink::GrapefruitJuice, NonAlcoholDrink::OrangeJuice,
                                             NonAlcoholDrink::Fanta, NonAlcoholDrink::SevenUp,
                                             NonAlcoholDrink::SevenUp, NonAlcoholDrink::LimeJuice, NonAlcoholDrink::Fanta};

    shots_stand<Cocktail> expected {Cocktail::Gimlet, Cocktail::Greyhount, Cocktail::Oops,
                                   Cocktail::Oops, Cocktail::Oops,
                                   Cocktail::SevenPlusSeven, Cocktail::Oops, Cocktail::Oops};

    EXPECT_EQ(expected, mix(alcohol, nonAlcohol, mixer));
}
