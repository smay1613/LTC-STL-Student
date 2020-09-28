#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto selectorInvokerFunc = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector){
        auto requestDataFunc = [](const IDataSelector* selector, std::vector<size_t> &outp ){
            return selector->getDataType1(outp, 0);
        };
        
        return invokeDataRequest(requestDataFunc, selector, returnValues);
    };

    return safeCall(userId, selectorInvokerFunc);
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto selectorInvokerFunc = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector){
        auto requestDataFunc = [](const IDataSelector* selector, std::vector<size_t> &outp ){
            return selector->getDataType2(outp);
        };

        return invokeDataRequest(requestDataFunc, selector, returnValues);
    };

    return safeCall(userId, selectorInvokerFunc);
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto selectorInvokerFunc = [this, &returnValues](const std::unique_ptr<IDataSelector>& selector){
        auto requestDataFunc = [this](const IDataSelector* selector, std::vector<std::string> &outp ){
            std::deque<size_t> unprocessedResults {};
            bool success {selector->getDataType3(unprocessedResults)};
            outp = process(unprocessedResults);
            return success;
        };
        
        return invokeDataRequest(requestDataFunc, selector, returnValues);
    };

    return safeCall(userId, selectorInvokerFunc);
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
