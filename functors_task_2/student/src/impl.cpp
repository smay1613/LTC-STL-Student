#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto call1 = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector)
    {
        using namespace std::placeholders;
        return invokeDataRequest(std::bind(&IDataSelector::getDataType1, _1, _2, 0), selector, returnValues);
    };

    return safeCall(userId, call1);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto call2 = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector)
    {
        using namespace std::placeholders;
        return invokeDataRequest(std::bind(&IDataSelector::getDataType2, _1, _2), selector, returnValues);
    };

    return safeCall(userId, call2);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto call3 = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector)
    {
        using namespace std::placeholders;

        std::deque<size_t> unprocessedResults {};
        bool success {
            invokeDataRequest(std::bind(&IDataSelector::getDataType3, _1, _2), selector, unprocessedResults)
        };

        returnValues = process(unprocessedResults);
        return success;
    };

    return safeCall(userId, call3);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
