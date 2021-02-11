#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.h"
#include <algorithm>

class Generator : public ::testing::Test
{
protected:
    const wall_shelf<6> expectedShelfPart {BeerBrand::HoeGaarden,
                                     BeerBrand::Corona,
                                     BeerBrand::Carlsberg,
                                     BeerBrand::Bud,
                                     BeerBrand::ZlataPraha,
                                     BeerBrand::Leffe};

    template<size_t shelfSize>
    size_t countShelfParts(const wall_shelf<shelfSize>& shelf) const
    {
        size_t subsequencesCount {0};

        auto findExpectedShelfPart = [&](auto begin_it) {
            return std::search(begin_it, shelf.end(),
                               expectedShelfPart.begin(), expectedShelfPart.end());
        };

        for (auto shelfCellIt = shelf.begin();
             shelfCellIt != shelf.end();
             findExpectedShelfPart(shelfCellIt))
        {
            if (std::distance(shelfCellIt, shelf.end()) >= expectedShelfPart.size())
            {
                ++subsequencesCount;
                std::advance(shelfCellIt, expectedShelfPart.size());
            }
            else
            {
                break;
            }
        }

        return subsequencesCount;
    }
};

class Predicate : public ::testing::Test
{
protected:
    auto isEqualTo(const BeerBrand brand)
    {
        return std::bind(std::equal_to<BeerBrand> {}, brand, std::placeholders::_1);
    }
};

template<BeerBrand... Args>
struct IsOrderedAndConsistent {
    static constexpr bool value = true;
};

template<BeerBrand A, BeerBrand B, BeerBrand... Args>
struct IsOrderedAndConsistent<A, B, Args...> {
    static constexpr bool value = static_cast<size_t>(A) <= static_cast<size_t>(B)
                                  && (static_cast<size_t>(A) == static_cast<size_t>(B) - 1)
                                  && IsOrderedAndConsistent<B, Args...>::value;
};
