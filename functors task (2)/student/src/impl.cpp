#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto lambda = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) {
        auto adaptor = [this](const IDataSelector* pSelector, std::vector<size_t>& data)
        {
            return pSelector->getDataType1(data, 0);
        };
        return adaptor(selector.get(), returnValues);
    };
    return safeCall(userId, lambda);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto lambda = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) {
        auto adaptor = [this](const IDataSelector* pSelector, std::vector<size_t>& data)
        {
            return pSelector->getDataType2(data);
        };
        return adaptor(selector.get(), returnValues);
    };
    return safeCall(userId, lambda);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto lambda = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) {
        std::deque<size_t> unprocessedResults {};
        auto adaptor = mem_fn(&IDataSelector::getDataType3);
        bool success {invokeDataRequest(adaptor, selector, unprocessedResults)};
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
