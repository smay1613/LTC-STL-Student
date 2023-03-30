#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto dataType1 = [this, &returnValues](const std::unique_ptr<IDataSelector>& dataSelector) {
        using namespace std::placeholders;
        return invokeDataRequest(std::bind(&IDataSelector::getDataType1, _1, _2, 0), dataSelector, returnValues);
    };

    return safeCall(userId, dataType1);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto dataType2 = [this, &returnValues](const std::unique_ptr<IDataSelector>& dataSelector) {
        using namespace std::placeholders;
        return invokeDataRequest(std::bind(&IDataSelector::getDataType2, _1, _2), dataSelector, returnValues);
    };

    return safeCall(userId, dataType2);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto dataType3 = [this, &returnValues](const std::unique_ptr<IDataSelector>& dataSelector) {
        std::deque<size_t> unprocessedResults{};

        using namespace std::placeholders;
        bool result{ invokeDataRequest(std::bind(&IDataSelector::getDataType3, _1, _2), dataSelector, unprocessedResults) };
        returnValues = process(unprocessedResults);

        return result;
    };

    return safeCall(userId, dataType3);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
