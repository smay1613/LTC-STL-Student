#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.h"
#include <vector>
#include <list>
#include <numeric>

template <typename T>
struct less_than
{
public:
    less_than (T foo) : val ( foo ) {}
    less_than (const less_than &rhs) : val ( rhs.val ) {}

    bool operator () (const T &v) const { return v < val; }
private:
    less_than ();
    less_than operator = (const less_than &rhs);
    T val;
};


struct GatherSequence : public ::testing::Test
{
    std::list<int> container;
    GatherSequence() : container(15) {}
protected:
    void SetUp() override
    {
        std::iota(container.begin(), container.end(), 5);
    }
};

struct GatherSequenceOfDuplicates : public ::testing::Test
{
    std::vector<int> container;
    GatherSequenceOfDuplicates() : container(10, 15) {}
};
