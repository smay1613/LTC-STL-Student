#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto lambdaExpression = [&returnValues](const std::unique_ptr<IDataSelector>& object) -> bool {
        return object->getDataType1(returnValues, 0);
    };
    return safeCall(userId, lambdaExpression);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto lambdaExpression = [&returnValues](const std::unique_ptr<IDataSelector>& object) -> bool {
        return object->getDataType2(returnValues);
    };
    return safeCall(userId, lambdaExpression);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    std::deque<size_t> unprocessedResults {};
    auto lambdaExpression = [&](const std::unique_ptr<IDataSelector>& object) -> bool {
        bool success = object->getDataType3(unprocessedResults);
        returnValues = process(unprocessedResults);
        return success;
    };
    return safeCall(userId, lambdaExpression);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
