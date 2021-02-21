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

    accumulator(Container& cont) {
        m_container = &cont;
    }
    const accumulator& operator*() const{
        return *this;
    }
    accumulator& operator*(){
        return *this;
    }
    const accumulator& operator++() const {
        return *this;
    }
    accumulator& operator++() {
        return *this;
    }

    template<class AnotherContainerType>
    accumulator& operator=(const AnotherContainerType& value){
        std::copy(value.cbegin(), value.cend(), std::inserter(*m_container, m_container->end()));
        return *this;
    }
    template<class AnotherContainerType>
    accumulator& operator=(AnotherContainerType&& value) noexcept{
        std::move(value.begin(), value.end(),  std::inserter(*m_container, m_container->end()));
        return *this;
    }
private:
    Container* m_container;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
