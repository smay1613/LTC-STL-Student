#pragma once
#include <iterator>

template <class Container>
struct accumulator
{
    /** @todo Iterator traits*/
    using difference_type = typename Container::difference_type;
    using value_type = typename Container::value_type;
    using pointer = typename Container::pointer;
    using reference = typename Container::reference;
    using iterator_category = typename std::output_iterator_tag;

    /** @todo Constructor with container*/
    accumulator(Container& cont) : m_container(cont) {}

    /** @todo lvalue writing operator*/
    template<typename T>
    accumulator<Container>& operator=(T& lvalue) {
        std::copy(lvalue.begin(), lvalue.end(), std::back_inserter(m_container));
        return *this;
    }

    /** @todo rvalue writing operator*/
    template<typename T>
    accumulator<Container>& operator=(T&& rvalue) {
        std::move(rvalue.begin(), rvalue.end(), std::back_inserter(m_container));
        return *this;
    }

    /** @todo Iterator operations */
    accumulator<Container>& operator++() {
        return *this;
    }
    accumulator<Container>& operator--() {
        return *this;
    }
    accumulator<Container>& operator*() {
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
