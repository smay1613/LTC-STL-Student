#include "maintest.h"
#include "impl.h"
#include <map>

template<BeerBrand... Args>
struct IsSorted {
    static constexpr bool value = true;
};

template<BeerBrand A, BeerBrand B, BeerBrand... Args>
struct IsSorted<A, B, Args...> {
    static constexpr bool value = static_cast<size_t>(A) <= static_cast<size_t>(B)
                                  && (static_cast<size_t>(A) == static_cast<size_t>(B) - 1) && IsSorted<B, Args...>::value;
};

static_assert (IsSorted<BeerBrand::None,
                       BeerBrand::HoeGaarden,
                       BeerBrand::Corona,
                       BeerBrand::Carlsberg,
                       BeerBrand::Bud,
                       BeerBrand::ZlataPraha,
                       BeerBrand::Leffe,
                       BeerBrand::Max>::value,
               "Enum values should be ordered and not changed!");

auto equalTo = [](const BeerBrand brand)
{
    return std::bind(std::equal_to<BeerBrand> {}, brand, std::placeholders::_1);
};

TEST(Generator, AllEntriesAreValid)
{
    wall_shelf<20> shelf;
    composeWallShelf(shelf, BeerOrganizer {});

    EXPECT_FALSE(std::any_of(shelf.begin(), shelf.end(),
                             equalTo(BeerBrand::None)));
    EXPECT_FALSE(std::any_of(shelf.begin(), shelf.end(),
                             equalTo(BeerBrand::Max)));
}

TEST(Generator, FullFit)
{
    wall_shelf<18> shelf;
    composeWallShelf(shelf, BeerOrganizer {});

    wall_shelf<6> expectedShelfPart {BeerBrand::HoeGaarden,
                                     BeerBrand::Corona,
                                     BeerBrand::Carlsberg,
                                     BeerBrand::Bud,
                                     BeerBrand::ZlataPraha,
                                     BeerBrand::Leffe};

    std::vector<wall_shelf<18>::iterator> subsequencesBegin;
    auto it = std::find(shelf.begin(), shelf.end(), BeerBrand::HoeGaarden);

    while (it != shelf.end())
    {
        subsequencesBegin.push_back(it);
        it = std::find(std::next(it),
                       shelf.end(),
                       BeerBrand::HoeGaarden);
    };

    EXPECT_EQ(subsequencesBegin.size(), 3);
    for (const auto& subsequence : subsequencesBegin)
    {
        EXPECT_TRUE(std::equal(expectedShelfPart.begin(),
                               expectedShelfPart.end(),
                               subsequence));
    }
}

TEST(Generator, SemiFit)
{
    wall_shelf<10> shelf;
    composeWallShelf(shelf, BeerOrganizer {});

    wall_shelf<6> expectedShelfPart {BeerBrand::HoeGaarden,
                                     BeerBrand::Corona,
                                     BeerBrand::Carlsberg,
                                     BeerBrand::Bud,
                                     BeerBrand::ZlataPraha,
                                     BeerBrand::Leffe};

    std::vector<wall_shelf<10>::iterator> subsequencesBegin;
    auto it = std::find(shelf.begin(), shelf.end(), BeerBrand::HoeGaarden);

    while (it != shelf.end())
    {
        subsequencesBegin.push_back(it);
        it = std::find(std::next(it),
                       shelf.end(),
                       BeerBrand::HoeGaarden);
    };

    EXPECT_EQ(subsequencesBegin.size(), 2);
    for (const auto& subsequence : subsequencesBegin)
    {
        auto elementsLeft = std::abs(std::distance(subsequence, shelf.end()));
        auto endOfSubSequenceIt = elementsLeft > expectedShelfPart.size() ?
                                                                      std::next(subsequence, expectedShelfPart.size())
                                                                      : shelf.end();
        EXPECT_TRUE(std::equal(subsequence,
                               endOfSubSequenceIt,
                               expectedShelfPart.begin()));
    }
}

TEST(Predicate, AllRemoved)
{
    wall_shelf<6> shelf;

    for (const auto& expensiveBeerType : {BeerBrand::Corona, BeerBrand::HoeGaarden})
    {
        shelf.fill(expensiveBeerType);
        removeBeerByCriteria(shelf, isExpensiveBeer);
        EXPECT_TRUE(std::all_of(shelf.begin(), shelf.end(),
                                equalTo(BeerBrand::None)));
    }
}

TEST(Predicate, NoRemoved)
{
    wall_shelf<6> shelf;

    for (const auto& nonExpensiveBeerType : {BeerBrand::Bud, BeerBrand::Leffe,
                                          BeerBrand::Carlsberg, BeerBrand::ZlataPraha})
    {
        shelf.fill(nonExpensiveBeerType);
        removeBeerByCriteria(shelf, isExpensiveBeer);
        EXPECT_TRUE(std::none_of(shelf.begin(), shelf.end(),
                                 equalTo(BeerBrand::None)));
    }
}

TEST(Predicate, DefaultShelf)
{
    wall_shelf<6> shelf;
    composeWallShelf(shelf, BeerOrganizer {});

    removeBeerByCriteria(shelf, isExpensiveBeer);

    EXPECT_EQ(std::count(shelf.begin(), shelf.end(),
                           BeerBrand::None),
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
    shelf.fill(BeerBrand::Leffe);
    std::fill(shelf.begin(), shelf.begin() + shelf.size() / 2,
              BeerBrand::HoeGaarden);

    EXPECT_TRUE(haveSameProperty(shelf, sameCountry));
}

TEST(Comparator, SameCountryDifferentBeer_Ukraine)
{
    wall_shelf<6> shelf;
    shelf.fill(BeerBrand::Bud);
    std::fill(shelf.begin(), shelf.begin() + shelf.size() / 2,
              BeerBrand::Carlsberg);
    shelf.front() = BeerBrand::ZlataPraha;

    EXPECT_TRUE(haveSameProperty(shelf, sameCountry));
}

TEST(Transform, AllCombinations)
{
    shots_stand<AlcoholDrink> alcohol;
    shots_stand<NonAlcoholDrink> nonAlcohol;

    size_t notOopsCount {0};
    for (const auto& drink1 : {AlcoholDrink::Gin, AlcoholDrink::Beer, AlcoholDrink::Wine, AlcoholDrink::Whiskey})
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
                ++notOopsCount;
            }
        }
    }
    EXPECT_EQ(notOopsCount, 3);
}

TEST(Transform, AllOopsNonAlcohol)
{
    shots_stand<AlcoholDrink> alcohol;
    shots_stand<NonAlcoholDrink> nonAlcohol;

    size_t notOopsCount {0};
    for (const auto& drink1 : {AlcoholDrink::Gin, AlcoholDrink::Beer, AlcoholDrink::Wine, AlcoholDrink::Whiskey})
    {
        alcohol.fill(drink1);
        for (const auto& drink2 : {NonAlcoholDrink::Fanta,
                                   NonAlcoholDrink::OrangeJuice})
        {
            nonAlcohol.fill(drink2);
            shots_stand<Cocktail> mixed {mix(alcohol, nonAlcohol, mixer)};
            if (std::count(mixed.begin(), mixed.end(), Cocktail::Oops) == 0)
            {
                ++notOopsCount;
            }
        }
    }
    EXPECT_EQ(notOopsCount, 0);
}

TEST(Transform, AllOopsAlcohol)
{
    shots_stand<AlcoholDrink> alcohol;
    shots_stand<NonAlcoholDrink> nonAlcohol;

    size_t notOopsCount {0};
    for (const auto& drink1 : {AlcoholDrink::Beer, AlcoholDrink::Wine})
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
                ++notOopsCount;
            }
        }
    }
    EXPECT_EQ(notOopsCount, 0);
}

TEST(Transform, Mixed)
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
