#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{   
    auto fun_1 =[](const IDataSelector* data, std::vector<size_t> &returnValues){
        return data->getDataType1(returnValues, 0);

    };

    auto fun_2=[&](const  std::unique_ptr<IDataSelector> & data){
        return invokeDataRequest(fun_1,data,returnValues);

    };

    return safeCall(userId,fun_2);

 
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{   
  
     auto fun_1 =[](std::vector<size_t> &returnValues, const IDataSelector* data ){
        return data->getDataType2(returnValues);

    };

    auto fun_2=[&](const  std::unique_ptr<IDataSelector> & data){
        auto inverse=std::bind(fun_1,std::placeholders::_2,std::placeholders::_1);
        return invokeDataRequest(inverse,data,returnValues);

    };

    return safeCall(userId,fun_2);

}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{   
     auto fun_1 =[&](const IDataSelector* data, std::vector<std::string> &returnValues ){

        std::deque<size_t> unprocessedResults {};
        bool success =data->getDataType3(unprocessedResults);
        returnValues = process(unprocessedResults);
        return success;

    };

    auto fun_2=[&](const  std::unique_ptr<IDataSelector> & data){
       
        return invokeDataRequest(fun_1,data,returnValues);

    };
    
    return safeCall(userId,fun_2);

}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
