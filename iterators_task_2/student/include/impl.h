#pragma once
#include <iterator>

template <class Container>
struct accumulator
        : std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    /** @todo Iterator traits*/
    /** @todo Constructor with container*/
    explicit accumulator(Container& container): m_container(container) {};

    /** @todo lvalue writing operator*/
    template<class differentContainer>
    accumulator& operator=(differentContainer& container) {
        std::copy(container.begin(), container.end(), std::back_inserter(m_container));

        return *this;
    }

    /** @todo rvalue writing operator*/
    template<class differentContainer>
    accumulator& operator=(differentContainer&& container) {
        std::move(container.begin(), container.end(), std::back_inserter(m_container));

        return *this;
    }

    /** @todo Iterator operations */
    accumulator& operator*() { return *this; }
    accumulator& operator++() { return *this; }
    accumulator operator++(int) { return *this; }

private:
    Container &m_container;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
