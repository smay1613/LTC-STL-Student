#include "maintest.h"

using namespace ::testing;

auto getMockSelector = [](const DataBrowser& browser, const std::string& user) {
    auto* dataSelector = browser.m_dataReaders.find(user)->second.get();
    return dynamic_cast<MockDataSelector*>(dataSelector);
};

namespace
{
bool simulateCreationFail {false};
}

IDataSelector* getSelector()
{
    if (simulateCreationFail)
    {
        return nullptr;
    }
    return new MockDataSelector {};
}

TEST_F(SafeCall, CheckSafeCallForNullPointer)
{
    simulateCreationFail = true;
    const std::string userId {"100"};
    m_browser.userEnter(userId);
    auto dummy = [](const std::unique_ptr<IDataSelector>&) -> bool {
        ADD_FAILURE() << "Functor call is invalid for nullptr";
        return true;
    };
    ASSERT_FALSE(m_browser.safeCall(userId, dummy));
    simulateCreationFail = false;
    m_browser.userLeave("100");
}

TEST_F(SafeCall, CheckSafeCallPositive)
{
    auto functor = [](const std::unique_ptr<IDataSelector>&) {return true;};
    EXPECT_TRUE(m_browser.safeCall("1", functor));
    EXPECT_TRUE(m_browser.safeCall("2", functor));
}

TEST_F(InvokeDataRequestCall, ShouldCompileDifferentCallable_Lambda)
{
    std::vector<size_t> dummyData;
    std::unique_ptr<IDataSelector> selector {new MockDataSelector {}};

    bool lambdaCalled {false};

    auto lambda = [&](const IDataSelector*, std::vector<size_t>&) {
        lambdaCalled = true;
        return true;
    };

    m_browser.invokeDataRequest(lambda, selector, dummyData);
    EXPECT_TRUE(lambdaCalled);
}

TEST_F(InvokeDataRequestCall, ShouldCompileDifferentCallable_Bind)
{
    std::vector<size_t> dummyData;
    std::unique_ptr<IDataSelector> selector {new MockDataSelector {}};

    bool lambdaCalled {false};

    auto lambda = [&](const IDataSelector*, std::vector<size_t>&) {
        lambdaCalled = true;
        return true;
    };
    auto bindExpression = std::bind(lambda, std::placeholders::_1, std::placeholders::_2);

    m_browser.invokeDataRequest(bindExpression, selector, dummyData);
    EXPECT_TRUE(lambdaCalled);
}

TEST_F(InvokeDataRequestCall, ShouldCompileDifferentCallable_MemFn)
{

    std::vector<size_t> dummyData;
    auto mockSelector = new MockDataSelector {};
    std::unique_ptr<IDataSelector> selector {mockSelector};

    bool lambdaCalled {false};

    auto lambda = [&](std::vector<size_t>&) {
        lambdaCalled = true;
        return true;
    };
    auto memFn = std::mem_fn(&IDataSelector::getDataType2);

    ON_CALL(*mockSelector, getDataType2(_)).WillByDefault(lambda);
    EXPECT_CALL(*mockSelector, getDataType2(_)).Times(1);

    m_browser.invokeDataRequest(memFn, selector, dummyData);
    EXPECT_TRUE(lambdaCalled);
}

TEST_F(Regression, WrongUsers)
{
    const auto userId = "10";

    std::vector<size_t> dummy;
    std::vector<std::string> dummy1;

    EXPECT_FALSE(m_browser.getDataType1(userId, dummy));
    EXPECT_FALSE(m_browser.getDataType2(dummy, userId));
    EXPECT_FALSE(m_browser.getDataType3(userId, dummy1));
}

TEST_F(Regression, GetDataType1Data)
{
    const auto userId = "2";
    const MockDataSelector& selector {*getMockSelector(m_browser, userId)};

    std::vector<size_t> data {1, 2, 3};

    ON_CALL(selector, getDataType1(_, _))
            .WillByDefault(DoAll
                           (
                               SetArgReferee<0>(data), // <- data will be set
                               Return(true))
                           );

    EXPECT_CALL(selector, getDataType1(_, _)) // <- if getter will be called
            .Times(1);

    std::vector<size_t> output;
    EXPECT_TRUE(m_browser.getDataType1(userId, output));

    EXPECT_EQ(data, output); // <- data passed by selector must be set in output param
}

TEST_F(Regression, GetDataType2Data)
{
    const auto userId = "3";
    const MockDataSelector& selector {*getMockSelector(m_browser, userId)};

    std::vector<size_t> data {1, 2, 3};

    ON_CALL(selector, getDataType2(_))
            .WillByDefault(DoAll
                           (
                               SetArgReferee<0>(data), // <- data will be set
                               Return(true))
                           );

    EXPECT_CALL(selector, getDataType2(_)) // <- if getter will be called
            .Times(1);

    std::vector<size_t> output;
    EXPECT_TRUE(m_browser.getDataType2(output, userId));

    EXPECT_EQ(data, output); // <- data passed by selector must be set in output param
}

TEST_F(Regression, GetDataType3Data)
{
    const auto userId = "1";
    const MockDataSelector& selector {*getMockSelector(m_browser, userId)};

    std::deque<size_t> data {1, 2, 3};

    ON_CALL(selector, getDataType3(_))
            .WillByDefault(DoAll
                           (
                               SetArgReferee<0>(data), // <- data will be set
                               Return(true))
                           );

    EXPECT_CALL(selector, getDataType3(_)) // <- if getter will be called
            .Times(1);

    std::vector<std::string> output;
    EXPECT_TRUE(m_browser.getDataType3(userId, output));

    auto isProcessed = [](const size_t lhs, const std::string& rhs) {
        return std::to_string(lhs) == rhs;
    };

    EXPECT_EQ(data.size(), output.size());
    EXPECT_TRUE(std::equal(data.begin(), data.end(), output.begin(), isProcessed)); // <- all data processed
}

TEST_F(Regression, GetDataType1Result)
{
    const auto userId = "1";
    const MockDataSelector& selector {*getMockSelector(m_browser, userId)};

    ON_CALL(selector, getDataType1(_, _))
            .WillByDefault(Return(false));

    EXPECT_CALL(selector, getDataType1(_, _))
            .Times(1);

    std::vector<size_t> output;
    EXPECT_FALSE(m_browser.getDataType1(userId, output));
}

TEST_F(Regression, GetDataType2Result)
{
    const auto userId = "1";
    const MockDataSelector& selector {*getMockSelector(m_browser, userId)};

    ON_CALL(selector, getDataType2(_))
            .WillByDefault(Return(false));

    EXPECT_CALL(selector, getDataType2(_))
            .Times(1);

    std::vector<size_t> output;
    EXPECT_FALSE(m_browser.getDataType2(output, userId));
}

TEST_F(Regression, GetDataType3Result)
{
    const auto userId = "1";
    const MockDataSelector& selector {*getMockSelector(m_browser, userId)};

    ON_CALL(selector, getDataType3(_))
            .WillByDefault(Return(false));

    EXPECT_CALL(selector, getDataType3(_))
            .Times(1);

    std::vector<std::string> output;
    EXPECT_FALSE(m_browser.getDataType3(userId, output));
}

