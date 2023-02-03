#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
	return safeCall(userId,  [&](const std::unique_ptr<IDataSelector>& a) {
		auto lambda = [](const IDataSelector* a,std::vector<size_t> & returnValues){
			return a->getDataType1(returnValues, 0);
		};
		return invokeDataRequest(lambda, a,returnValues);
	});
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
	return safeCall(userId,  [&](const std::unique_ptr<IDataSelector>& a) {
		auto lambda = [](std::vector<size_t> & returnValues, const IDataSelector* a){
			return a->getDataType2(returnValues);
		};
		auto wrapper = std::bind(lambda, std::placeholders::_2, std::placeholders::_1);
		return invokeDataRequest(wrapper, a,returnValues);
	});
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
	return safeCall(userId,  [&](const std::unique_ptr<IDataSelector>& a) {
		auto lambda = [this](std::vector<std::string> & returnValues, const IDataSelector* a){
			std::deque<size_t> unprocessedResults {};
			bool success {a->getDataType3(unprocessedResults)};
			returnValues = process(unprocessedResults);
			return success;
		};
		return invokeDataRequest(lambda, a,returnValues);
	});
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
