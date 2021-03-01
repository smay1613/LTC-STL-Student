#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto requestCallback = [](const IDataSelector* selector, std::vector<size_t>& returnValues) {
        return selector->getDataType1(returnValues, 0);
    };

    auto safeCallCallback = [this, &returnValues, &requestCallback](const std::unique_ptr<IDataSelector>& selector) {
        return invokeDataRequest(requestCallback, selector, returnValues);
    };

    return safeCall(userId, safeCallCallback);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto requestCallback = [](const IDataSelector* selector, std::vector<size_t>& returnValues) {
        return selector->getDataType2(returnValues);
    };

    auto safeCallCallback = [this, &returnValues, &requestCallback](const std::unique_ptr<IDataSelector>& selector) {
        return invokeDataRequest(requestCallback, selector, returnValues);
    };

    return safeCall(userId, safeCallCallback);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto requestCallback = [](const IDataSelector* selector, std::deque<size_t>& returnValues) {
        return selector->getDataType3(returnValues);
    };

    auto safeCallCallback = [this, &returnValues, &requestCallback](const std::unique_ptr<IDataSelector>& selector) {
        std::deque<size_t> unprocessedResults {};
        bool success {invokeDataRequest(requestCallback, selector, unprocessedResults)};
        returnValues = process(unprocessedResults);
        return success;
    };

    return safeCall(userId, safeCallCallback);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
