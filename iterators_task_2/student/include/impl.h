#pragma once
#include <iterator>

template <class Container>
class accumulator : public std::iterator<std::output_iterator_tag, typename Container::value_type>
{
    /** @todo Iterator traits*/
    /** @todo Constructor with container*/
    /** @todo lvalue writing operator*/
    /** @todo rvalue writing operator*/

    /** @todo Iterator operations */

public:
    using ValueType = typename Container::value_type;

    accumulator operator*() const{
        return *this;
    }

    const accumulator& operator++() const {
        return *this;
    }
    accumulator& operator++() {
        return *this;
    }
    accumulator& operator=(const ValueType& value){
        container->push_back(value);
        return *this;
    }
private:
    Container* container;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
}
