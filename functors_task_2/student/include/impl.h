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
        m_dataReaders.emplace(userId, std::unique_ptr<IDataSelector>(getSelector()));
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
     * @todo SafeCall idiom
     * You should implement this method, that is responsible for request validation.
     * If request is valid (user exists and a valid selector exists),
     * this method calls passed callback with a valid selector pointer
     */
    template <typename T>
    bool safeCall(const std::string &userId, T&& f) const
    {
        static_assert(std::is_same<decltype(f(nullptr)), bool>::value, "Provided Callable must return bool");
        // find reader
        // check for errors
        // call functor
        return false;
    }

    /**
     * @todo You should implement this method, that is responsible for a "general" data requesting
     * General data request will return bool, accept the selector and output param
     * You must adapt functors before invocation
     */
    template<class Functional, typename Output>
    bool invokeDataRequest(Functional method, const std::unique_ptr<IDataSelector>& selector, Output& result) const
    {
        // adapt function
        // call selector member
        return false;
    }
};
