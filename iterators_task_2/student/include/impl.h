#pragma once
#include <iterator>
#include <algorithm>

template <class Container>
struct accumulator
{
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using iterator_category = std::output_iterator_tag;

    accumulator(Container& container)
        : m_ref(container)
    {}

    accumulator(const accumulator<Container>& other) = default;
    accumulator<Container>& operator=(const accumulator<Container>& other) = default;

    template <typename AnotherContainer>
    accumulator& operator=(const AnotherContainer& container)
    {
        std::copy(container.cbegin(), container.cend(), std::back_inserter(m_ref.get()));
        return *this;
    }

    template <typename AnotherContainer>
    accumulator& operator=(AnotherContainer&& container){
        std::move(container.begin(), container.end(), std::back_inserter(m_ref.get()));
        return *this;
    }

    accumulator& operator++()
    {
        return *this;
    }

    accumulator<Container>& operator*()
    {
        return *this;
    }

private:
    std::reference_wrapper<Container> m_ref;
};

template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>{container};
}
