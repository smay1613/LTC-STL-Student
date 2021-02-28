#include "impl.h"
#include <functional>
#include <iostream>

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto method = [this, &returnValues] (const std::unique_ptr<IDataSelector> & selector) {
        const auto & getDataType1 = [] (IDataSelector * selector, std::vector<size_t> &returnV) {
            return selector->getDataType1(returnV, 0);
        };

        return invokeDataRequest(getDataType1, selector, returnValues);
    };

    return safeCall(userId, method);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto method = [this, &returnValues] (const std::unique_ptr<IDataSelector> & selector) {
        const auto & getDataType2 = [] (IDataSelector * selector, std::vector<size_t> &returnV) {
            return selector->getDataType2(returnV);
        };

        return invokeDataRequest(getDataType2, selector, returnValues);
    };

    return safeCall(userId, method);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto method = [this, &returnValues] (const std::unique_ptr<IDataSelector> & selector) {
        const auto & getDataType2 = [this] (IDataSelector * selector, std::vector<std::string> &returnV) {
            std::deque<size_t> unprocessedResults {};
            bool success {selector->getDataType3(unprocessedResults)};
            returnV = process(unprocessedResults);
            return success;
        };

        return invokeDataRequest(getDataType2, selector, returnValues);
    };

    return safeCall(userId, method);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
