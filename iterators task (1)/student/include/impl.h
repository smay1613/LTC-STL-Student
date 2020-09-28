#pragma once
#include <iterator>

template <class Container>
struct accumulator
{
    using iterator_category = std::output_iterator_tag;
    using value_type        = void;
    using difference_type   = void;
    using pointer           = void;
    using reference         = void;

    explicit accumulator(Container& container) : container_(container) {}

    template <class OtherContainer>
    accumulator& operator=(const OtherContainer& value)
    {
        container_.insert(container_.end(), value.begin(), value.end());
        return *this;
    }

    template <class OtherContainer>
    accumulator& operator=(OtherContainer&& value)
    {
        container_.insert(container_.end(),
                          std::make_move_iterator(value.begin()),
                          std::make_move_iterator(value.end()));
        return *this;
    }

    accumulator& operator*()     { return *this; }
    accumulator& operator++()    { return *this; }
    accumulator& operator++(int) { return *this; }

    Container& container_;
};

template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
