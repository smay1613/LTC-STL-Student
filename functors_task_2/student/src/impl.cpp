#include "impl.h"

using namespace std::placeholders;

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    return safeCall(userId, [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) -> bool {
                                    auto dataType = std::bind(&IDataSelector::getDataType1, _1, _2, 0);
                                    invokeDataRequest(dataType, selector, returnValues);
                                });
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    return safeCall(userId, [this, &returnValues](const std::unique_ptr<IDataSelector>& selector) -> bool {
                                    auto dataType = std::bind(&IDataSelector::getDataType2, _1, _2);
                                    invokeDataRequest(dataType, selector, returnValues);
                                });
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{

    std::deque<size_t> unprocessedResults {};
    bool success = safeCall(userId, [this, &unprocessedResults](const std::unique_ptr<IDataSelector>& selector) -> bool {
                                    auto dataType = std::bind(&IDataSelector::getDataType3, _1, _2);
                                    invokeDataRequest(dataType, selector, unprocessedResults);
                                });
    returnValues = process(unprocessedResults);
    return success;
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
