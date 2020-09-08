#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.h"

struct AnagramsPositive : public ::testing::TestWithParam<std::pair<std::string, std::string>>
{

};
