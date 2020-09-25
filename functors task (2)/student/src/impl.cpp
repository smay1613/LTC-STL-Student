#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto invokeDataRequestLambda = [this, & returnValues](const std::unique_ptr<IDataSelector>& selector)
    {
        auto getDataType1Lambda = [](const IDataSelector* selector, std::vector<size_t> &returnValues)
        {
            return selector->getDataType1(returnValues, 0);
        };
        return invokeDataRequest(getDataType1Lambda, selector, returnValues);
    };
    return safeCall(userId, invokeDataRequestLambda);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto invokeDataRequestLambda = [this, & returnValues](const std::unique_ptr<IDataSelector>& selector)
    {
        auto getDataType2Lambda = [](const IDataSelector* selector, std::vector<size_t> &returnValues)
        {
            return selector->getDataType2(returnValues);
        };
        return invokeDataRequest(getDataType2Lambda, selector, returnValues);
    };
    return safeCall(userId, invokeDataRequestLambda);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto invokeDataRequestLambda = [this, & returnValues](const std::unique_ptr<IDataSelector>& selector)
    {
        auto processDataType3Lambda = [this](const IDataSelector* selector, std::vector<std::string> &returnValues)
        {
            std::deque<size_t> unprocessedResults {};
            bool success{selector->getDataType3(unprocessedResults)};
            returnValues = process(unprocessedResults);
            return success;
        };
        return invokeDataRequest(processDataType3Lambda, selector, returnValues);
    };
    return safeCall(userId, invokeDataRequestLambda);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
