#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}



/** @todo THIS METHOD MUST USE safeCall idiom AND invokeDataRequest ON SUCCESS
* "normal" method
*/
bool DataBrowser::getDataType1(const std::string& userId, std::vector<size_t>& returnValues) const
{
    return safeCall(userId,
        [this, &returnValues](const std::unique_ptr<IDataSelector>& selector)
        {
            using namespace std::placeholders;
            auto method = std::bind(&IDataSelector::getDataType1, _1, _2, 0);
            return invokeDataRequest(method, selector, returnValues);
        }
    );
}

/** @todo THIS METHOD MUST USE safeCall idiom AND invokeDataRequest ON SUCCESS
* method with non-standard order of arguments
*/
bool DataBrowser::getDataType2(std::vector<size_t>& returnValues, const std::string& userId) const
{
    return safeCall(userId,
        [this, &returnValues](const std::unique_ptr<IDataSelector>& selector)
        {
            auto method = &IDataSelector::getDataType2;
            return invokeDataRequest(method, selector, returnValues);
        }
    );
}

/** THIS METHOD MUST USE safeCall idiom AND invokeDataRequest ON SUCCESS
 * method with non-standard output param
 */
bool DataBrowser::getDataType3(const std::string& userId, std::vector<std::string>& returnValues) const
{
    return safeCall(userId,
        [this, &returnValues](const std::unique_ptr<IDataSelector>& selector)
        {
            using namespace std::placeholders;
            auto method = [this](const IDataSelector* selector, std::vector<std::string>& result)
            {
                std::deque<size_t> deque;
                bool success = selector->getDataType3(deque);
                result = process(deque);
                return success;
            };
            return invokeDataRequest(method, selector, returnValues);
        }
    );
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
