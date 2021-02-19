#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto lambda = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) {
        return invokeDataRequest(std::bind(&IDataSelector::getDataType1,
                                           std::placeholders::_1, std::placeholders::_2, 0), selector, returnValues);
    };

    return safeCall(userId, lambda);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto lambda = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) {
        return invokeDataRequest(std::bind(&IDataSelector::getDataType2,
                                           std::placeholders::_1, std::placeholders::_2), selector, returnValues);
    };

    return safeCall(userId, lambda);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto lambda = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) {
        std::deque<size_t> unprocessedResults {};
        bool success = invokeDataRequest(std::bind(&IDataSelector::getDataType3,
                                                   std::placeholders::_1, std::placeholders::_2), selector, unprocessedResults);
        returnValues = process(unprocessedResults);
        return success;
    };

    return safeCall(userId, lambda);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
