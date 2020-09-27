#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto safeCallAdapter = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) {
        auto invokeDataRequestAdapter
            = [](IDataSelector* selector, std::vector<size_t>& values) {
                return selector->getDataType1(values, 0);
            };
        return invokeDataRequest(invokeDataRequestAdapter, selector, returnValues);
    };

    return safeCall(userId, safeCallAdapter);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto safeCallAdapter = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) {
        auto invokeDataRequestAdapter
            = [](IDataSelector* selector, std::vector<size_t>& values) {
                return selector->getDataType2(values);
            };
        return invokeDataRequest(invokeDataRequestAdapter, selector, returnValues);
    };

    return safeCall(userId, safeCallAdapter);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto safeCallAdapter = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) {
        auto invokeDataRequestAdapter
            = [this](IDataSelector* selector, std::vector<std::string>& values) {

                std::deque<size_t> unprocessedResults {};
                bool success {selector->getDataType3(unprocessedResults)};
                values = process(unprocessedResults);
                return success;
            };
        return invokeDataRequest(invokeDataRequestAdapter, selector, returnValues);
    };

    return safeCall(userId, safeCallAdapter);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
