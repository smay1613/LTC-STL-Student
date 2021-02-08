#pragma once
#include <vector>
#include <deque>

/**
 * @warning
 * YOU ARE NOT ALLOWED TO CHANGE PUBLIC API!

 * PLEASE NOTE THAT IT IS AN EXAMPLE OF AWFUL DESIGN.
 * DO NOT TRY TO USE IT IN REAL LIFE.
 * It is easier to rewrite than making such things.
 * But, for training, it is a challenging task.
 */

class IDataSelector
{
public:
    virtual ~IDataSelector() = default;
    /**
     * Challenge method with deprecated param, that should allways be zero
     */
    virtual bool getDataType1(std::vector<size_t>& returnValues,
                              const size_t unusedDataShouldBeZero) const = 0;
    /**
     * Normal method
     */
    virtual bool getDataType2(std::vector<size_t>& returnValues) const = 0;

    /**
     * Maintainer added method with another signature
     */
    virtual bool getDataType3(std::deque<size_t>& returnValues) const = 0;

};
