#include "impl.h"

#include <deque>

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

void DataBrowser::userEnter(const std::string& userId)
{
    m_dataReaders.emplace(userId, getSelector());
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    // Variant #1: Lambda and std::bind().

    auto getDataTypeAdapter = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector)
    {
        using namespace std::placeholders;
        return invokeDataRequest(
            std::bind(&IDataSelector::getDataType1, _1, _2, 0), selector, returnValues);
    };
    return safeCall(userId, getDataTypeAdapter);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    // Variant #2: Two lambdas.

    auto getDataTypeAdapter = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector)
    {
        auto getDataTypeCaller = [](const IDataSelector* selector, std::vector<size_t>& returnValues)
        {
            return selector->getDataType2(returnValues);
        };
        return invokeDataRequest(getDataTypeCaller, selector, returnValues);
    };
    return safeCall(userId, getDataTypeAdapter);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    // Variant #3: One lambda only. Looks like the simplest variant, but violates requirement of
    //             calling invokeDataRequest() method.

    auto getDataTypeAdapter = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector)
    {
        std::deque<size_t> unprocessedReturnValues;
        const bool success = selector->getDataType3(unprocessedReturnValues);
        returnValues = process(unprocessedReturnValues);
        return success;
    };
    return safeCall(userId, getDataTypeAdapter);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
