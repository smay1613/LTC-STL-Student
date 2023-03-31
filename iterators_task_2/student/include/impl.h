#pragma once
#include <iterator>

template <class Container>
struct accumulator
{
    /** @todo Iterator traits*/
    using iterator_category = typename std::output_iterator_tag;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using value_type = void;

    /** @todo Constructor with container*/
    accumulator(Container& container) : container{ container } {}

    /** @todo lvalue writing operator*/
    template<typename T>
    accumulator<Container>& operator=(const T& value) {
        container.insert(container.end(), value.begin(), value.end());
        return *this;
    }

    /** @todo rvalue writing operator*/
    template<typename T>
    accumulator<Container>& operator=(T&& value) {
        std::move(value.begin(), value.end(), std::back_inserter(container));
        return *this;
    }

    /** @todo Iterator operations */
    accumulator<Container>& operator*() { return *this; }
    accumulator<Container>& operator++() { return *this; }
    accumulator<Container>& operator--() { return *this; }

private:
    Container& container;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
