#pragma once
#include <iterator>

template <class Container>
struct accumulator : public std::iterator<std::output_iterator_tag, void,void,void,void>
{

    /** @todo Constructor with container*/
    accumulator(Container& container) : m_cotainer(container)
    {}

    /** @todo lvalue writing operator*/
    template <typename OtherContainer>
    accumulator& operator=(const OtherContainer& input) {
        std::copy(input.cbegin(), input.cend(), std::back_inserter(m_cotainer));

        return *this;
    }

    /** @todo rvalue writing operator*/
    template <typename OtherContainer>
    accumulator& operator=(OtherContainer&& input) {
        std::move(input.begin(), input.end(), std::back_inserter(m_cotainer));

        return *this;
    }

    /** @todo Iterator operations */
    accumulator& operator*() {
        return *this;
    }

    accumulator& operator++() {
        return *this;
    }

    accumulator operator++(int) {
        return *this;
    }

private:
    Container &m_cotainer;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
