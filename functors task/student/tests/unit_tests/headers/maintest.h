#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <vector>
#define private public // <- communism
#include "impl.h"

class Regression : public ::testing::Test
{
public:
    void SetUp() override
    {
        m_browser.userEnter("1");
        m_browser.userEnter("2");
        m_browser.userEnter("3");
        m_browser.userEnter("4");
        m_browser.userEnter("5");
    }
protected:
    DataBrowser m_browser;
};

class SafeCall : public Regression
{
};

class InvokeDataRequestCall : public Regression
{
};

class MockDataSelector : public IDataSelector
{
public:
    MOCK_METHOD(bool, getDataType1,
                (std::vector<size_t>& returnValues, const size_t unusedDataShouldBeZero),
                (override, const));
    MOCK_METHOD(bool, getDataType2,
                (std::vector<size_t>& returnValues),
                (override, const));
    MOCK_METHOD(bool, getDataType3,
                (std::deque<size_t>& returnValues),
                (override, const));
};
