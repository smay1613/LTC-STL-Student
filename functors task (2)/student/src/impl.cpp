#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    const auto& it = m_dataReaders.find(userId);
    if (it == m_dataReaders.cend())
    {
        return false;
    }
    if (it->second == nullptr)
    {
        return false;
    }
    return it->second->getDataType1(returnValues, 0);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    const auto& it = m_dataReaders.find(userId);
    if (it == m_dataReaders.cend())
    {
        return false;
    }
    if (it->second == nullptr)
    {
        return false;
    }
    return it->second->getDataType2(returnValues);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    const auto& it = m_dataReaders.find(userId);
    if (it == m_dataReaders.cend())
    {
        return false;
    }
    if (it->second == nullptr)
    {
        return false;
    }

    std::deque<size_t> unprocessedResults {};
    bool success {it->second->getDataType3(unprocessedResults)};
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
