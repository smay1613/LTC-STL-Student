#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto method = [](const IDataSelector* selector, std::vector<size_t> &returnValues)
    {
        return selector->getDataType1(returnValues, 0);
    };
    auto f = [&](const std::unique_ptr<IDataSelector>& selector) 
    {
        return invokeDataRequest(method, selector, returnValues);
    };

    return safeCall(userId, f);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto method = [](const IDataSelector* selector, std::vector<size_t> &returnValues)
    {
        return selector->getDataType2(returnValues);
    };
    auto f = [&](const std::unique_ptr<IDataSelector>& selector) 
    {
        return invokeDataRequest(method, selector, returnValues);
    };

    return safeCall(userId, f);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto method = [&](const IDataSelector* selector, std::vector<std::string> &returnValues)
    {
        std::deque<size_t> unprocessedResults {};
        bool success = selector->getDataType3(unprocessedResults);
        returnValues = process(unprocessedResults);
        return success;
    };
    auto f = [&](const std::unique_ptr<IDataSelector>& selector) 
    {
        return invokeDataRequest(method, selector, returnValues);
    };

    return safeCall(userId, f);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
