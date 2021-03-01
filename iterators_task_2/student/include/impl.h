#pragma once
#include <iterator>

template <class Container>
struct accumulator
{
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

    explicit accumulator(Container& container)
        : mContainer{container}
    {
    }

    template<class Other>
    accumulator& operator=(const Other& other)
    {
        std::copy(std::begin(other), std::end(other), std::back_inserter(mContainer));
        return *this;
    }

    template<class Other>
    accumulator& operator=(Other&& other)
    {
        std::move(std::begin(other), std::end(other), std::back_inserter(mContainer));
        return *this;
    }

    accumulator& operator*()
    {
        return *this;
    }

    accumulator& operator++()
    {
        return *this;
    }

    accumulator operator++(int)
    {

    }
private:
    Container& mContainer;
};

template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
