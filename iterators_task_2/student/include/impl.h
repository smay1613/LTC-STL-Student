#pragma once
#include <iterator>

template <class Container>
struct accumulator
{
    /** @todo Iterator traits*/

    using value_type = typename Container::value_type ;
    using difference_type = typename Container::difference_type ;
    using iterator_category = typename std::output_iterator_tag;
    using pointer = typename Container::pointer ;
    using reference = typename Container::reference ;

    /** @todo Constructor with container*/

    accumulator(Container &otherContainer)
        : m_container(otherContainer) {}

    /** @todo lvalue writing operator*/
    template <class OtherContainer>
    accumulator& operator=(OtherContainer &input)
    {
        std::copy(input.begin(), input.end(), std::inserter(m_container,m_container.end()));
        return *this;
    }

    /** @todo rvalue writing operator*/

    template <class OtherContainer>
    accumulator& operator=(OtherContainer&& input)
    {
        std::move(input.begin(), input.end(), std::inserter(m_container,m_container.end()));

        return *this;
    }

    /** @todo Iterator operations */
    accumulator& operator*()
    {
        return *this;
    }
    accumulator& operator++()
    {
        return *this;
    }
    accumulator operator--()
    {
        return *this;
    }

private:
    Container& m_container;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
