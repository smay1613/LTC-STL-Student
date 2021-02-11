#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.h"

#include <list>
#include <numeric>

struct X
{
    int a = -1;
    bool moved_from = false;

    X() = default;

    X(int a)
        : a(a)
    { }

    X(const X&) = delete;
    X& operator=(const X&) = delete;

    X(X&& other)
    {
        if (this != &other)
            *this = std::move(other);
    }

    X&
    operator=(X&& other)
    {
        a = other.a;
        other.moved_from = true;
        moved_from = false;
        return *this;
    }
};

struct Shift : public ::testing::Test
{
    static constexpr size_t N = 15;
    std::list<X> cx;

    void SetUp() override
    {
        cx.resize(N);
        std::iota(cx.begin(), cx.end(), 0);
    }
};
