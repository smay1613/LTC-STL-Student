#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    return safeCall(userId, [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) {
        return invokeDataRequest([](const IDataSelector* selector, std::vector<size_t>& returnValues) {
            return selector->getDataType1(returnValues, 0);
        },
        selector,
        returnValues);
    });

    return true;
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    return safeCall(userId, [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) -> bool {
        return invokeDataRequest([](const IDataSelector* selector, std::vector<size_t>& returnValues) {
            return selector->getDataType2(returnValues);
        },
        selector,
        returnValues);
    });

    return true;
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    return safeCall(userId, [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) {
        std::deque<size_t> unprocessedResults {};
        bool success {invokeDataRequest([](const IDataSelector* selector, std::deque<size_t>& returnValues) {
                return selector->getDataType3(returnValues);
            },
            selector,
            unprocessedResults)};
        returnValues = process(unprocessedResults);
        return success;
    });

    return true;
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
