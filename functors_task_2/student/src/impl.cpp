#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    using namespace std::placeholders;

    auto convertedMethod ([&](const std::unique_ptr<IDataSelector>& selector) {
        return invokeDataRequest(std::bind(&IDataSelector::getDataType1, _1, _2, 0), selector, returnValues);
    });
    return safeCall(userId, convertedMethod);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto convertedMethod ([&](const std::unique_ptr<IDataSelector>& selector) {
        return invokeDataRequest(&IDataSelector::getDataType2, selector, returnValues);
    });
    return safeCall(userId, convertedMethod);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto convertedMethod ([&](const std::unique_ptr<IDataSelector>& selector) {
        std::deque<size_t> unprocessedResults {};
        bool result = invokeDataRequest(&IDataSelector::getDataType3, selector, unprocessedResults);
        returnValues = process(unprocessedResults);
        return result;
    });
    return safeCall(userId, convertedMethod);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
