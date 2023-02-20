#pragma once
#include <iterator>

template <class Container>
struct accumulator
{   
    public:
    /** @todo Iterator traits*/
    using iterator_category=  std::output_iterator_tag;
    using value_type= void;
    using difference_type=void;
    using pointer=void;
    using reference=void;

    /** @todo Constructor with container*/
    accumulator( Container & container): m_container(container){}
    /** @todo lvalue writing operator*/
    template<typename T> 
    accumulator & operator=(const T & value){
        std::copy(value.begin(),value.end(),std::back_inserter(m_container));
        return *this;
    }
    /** @todo rvalue writing operator*/
    template<typename T> 
    accumulator & operator=( T && value){
        std::move(value.begin(),value.end(),std::back_inserter(m_container));
        return *this;
    }
    /** @todo Iterator operations */
    accumulator & operator*() { return *this; } 
    accumulator & operator++() { return *this; }
    accumulator operator++(int) { return *this; } 

    private:
    Container & m_container;

};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
    
}
