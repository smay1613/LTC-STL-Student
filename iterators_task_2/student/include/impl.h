#pragma once
#include <iterator>

template <class Container>
struct accumulator
        : public std::iterator<std::output_iterator_tag, void, void, void, void>

{
    explicit accumulator(Container& c)
        : m_container(c)
    {
    }

    template<typename Input>
    accumulator& operator=(const Input& input) {
        std::copy(input.cbegin(), input.cend(), std::back_inserter(m_container));
        return *this;
    }

    template<typename Input>
    accumulator& operator=(Input&& input) {
        std::move(input.begin(), input.end(), std::back_inserter(m_container));
        return *this;
    }

    accumulator& operator++() {
        return *this;
    }

    accumulator operator++(int) {
        return *this;
    }

    accumulator& operator*() {
        return *this;
    }

private:
    Container& m_container;
};

template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
