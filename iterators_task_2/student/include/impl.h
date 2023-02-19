#pragma once
#include <iterator>

template <class Container>
struct accumulator
{
protected:
    Container& m_container;

public:
    /** @todo Iterator traits*/
    typedef typename Container::value_type value_type;
    typedef typename Container::difference_type difference_type;
    typedef typename std::output_iterator_tag iterator_category;
    typedef typename Container::pointer pointer;
    typedef typename Container::reference reference;

    /** @todo Constructor with container*/
    accumulator(Container& otherContainer) : m_container(otherContainer) {}

    /** @todo lvalue writing operator*/
    template <class OtherContainer>
    accumulator& operator=(OtherContainer const& input) {
        std::copy(input.cbegin(), input.cend(), std::back_inserter(m_container));
        return *this;
    }

    /** @todo rvalue writing operator*/
    template <class OtherContainer>
    accumulator& operator=(OtherContainer&& input) {
        std::move(input.begin(), input.end(), std::back_inserter(m_container));
        return *this;
    }

    /** @todo Iterator operations */
    accumulator& operator*() { return *this; }
    accumulator& operator++() { return *this; }
    accumulator operator++(int) { return *this; }
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
