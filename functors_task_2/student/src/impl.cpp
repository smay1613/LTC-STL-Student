#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto func = [&](const std::unique_ptr<IDataSelector>& selector) {
        return invokeDataRequest(
            [](const IDataSelector* selector, std::vector<size_t> &returnValues) {
                return selector->getDataType1(returnValues, 0);
            },
            selector, returnValues
        );
    };
    return safeCall(userId, func);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto func = [&](const std::unique_ptr<IDataSelector>& selector) {
        return invokeDataRequest(
            [](std::vector<size_t> &returnValues, const IDataSelector* selector) {
                return selector->getDataType2(returnValues);
            },
            selector, returnValues
        );
    };
    return safeCall(userId, func);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto func = [&](const std::unique_ptr<IDataSelector>& selector) {
        return invokeDataRequest([&](const IDataSelector* selector, std::vector<std::string> &returnValues) {
            std::deque<size_t> unprocessedResults {};
            bool success = selector->getDataType3(unprocessedResults);
            returnValues = process(unprocessedResults);
            return success;
        },
        selector, returnValues
        );
    };
    return safeCall(userId, func);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
