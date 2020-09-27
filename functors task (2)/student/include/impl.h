#pragma once
#include <map>
#include <memory>
#include <functional>
#include <algorithm>
#include "selector.h"

// for testing purposes
extern IDataSelector* getSelector();

class DataBrowser
{
public:
    /**
     * Removes data reader by key
     */
    void userLeave(const std::string& userId);

    /**
     * Adds data reader to map
     */
    void userEnter(const std::string& userId)
    {  // awful, but in header for testing
        m_dataReaders.emplace(userId, getSelector());
    }

    /** @todo THIS METHOD MUST USE safeCall idiom AND invokeDataRequest ON SUCCESS
    * "normal" method
    */
    bool getDataType1(const std::string& userId, std::vector<size_t>& returnValues) const;

    /** @todo THIS METHOD MUST USE safeCall idiom AND invokeDataRequest ON SUCCESS
    * method with non-standard order of arguments
    */
    bool getDataType2(std::vector<size_t>& returnValues, const std::string& userId) const;

    /** THIS METHOD MUST USE safeCall idiom AND invokeDataRequest ON SUCCESS
     * method with non-standard output param
     */
    bool getDataType3(const std::string& userId, std::vector<std::string>& returnValues) const;

    // getDataType55...
private:
    // dummy processing for making task harder
    template<class T>
    std::vector<std::string> process(const T& source) const;

    /**
     * Each user has an asociated data reader
     */
    std::map<std::string /*userId*/,
            std::unique_ptr<IDataSelector> /* database selector - imagine that it is interface */
            > m_dataReaders;

    /**
     * Checks user id for existing and valid selector and performs the call of data request.
     * Passed @param f must have the signature bool(const std::unique_ptr<IDataSelector>&)
     */
    template <typename T>
    bool safeCall(const std::string &userId, T&& f) const;

    /**
     * General data requesting via a single interface.
     * Passed @param method should have the signature bool(IDataSelector*, std::vector<size_t>&)
     * and represents adapted function which requests data via selector and saves results in result
     */
    template<class Functional, typename Output>
    bool invokeDataRequest(Functional method, const std::unique_ptr<IDataSelector>& selector, Output& result) const
    {
        return method(selector.get(), result);
    }
};

template <typename T>
bool DataBrowser::safeCall(const std::string &userId, T&& f) const
{
    static_assert(
        std::is_same<decltype(f(nullptr)), bool>::value,
        "Provided Callable must return bool");

    const auto& it = m_dataReaders.find(userId);

    if (it == m_dataReaders.cend()) {
        return false;
    }
    if (it->second == nullptr) {
        return false;
    }

    return f(it->second);
}
