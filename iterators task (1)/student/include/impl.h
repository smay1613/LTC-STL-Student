#pragma once
#include <iterator>

template <class Container>
struct accumulator
{
    /** @todo Iterator traits*/
    using iterator_category = typename std::output_iterator_tag;
    using value_type        = Container;
    using difference_type   = std::ptrdiff_t;
    using pointer           = value_type*;
    using reference         = value_type&;

    /** @todo Constructor with container*/
    accumulator(Container& container) : mContainer(&container) {}
    /** @todo Copy assignment operator*/
    accumulator<Container>(const accumulator<Container>&) = default;
    accumulator<Container>& operator=(const accumulator<Container>&) = default;
    /** @todo Move assignment operator*/
    accumulator<Container>(accumulator<Container>&& val) = default;
    accumulator<Container>& operator=(accumulator<Container>&& val) = default;

    /** @todo Iterator operations */
    accumulator<Container>& operator++()
    {
        return *this;
    }
    accumulator<Container>& operator*()
    {
        return *this;
    }

    ///Mixin interface for an iterator & reference type is not
    ///a canonical way to implement iterators.
    ///Nevertheless it is done so for the sake of simplicity.
    template<typename C2>
    accumulator<Container>& operator=(C2&& c2)
    {
        mContainer->insert(mContainer->end(),
            std::make_move_iterator(c2.begin()), std::make_move_iterator(c2.end())
        );
        return *this;
    }

    template<typename C2>
    accumulator<Container>& operator=(const C2& c2)
    {
        mContainer->insert(mContainer->end(), c2.begin(), c2.end());
        return *this;
    }
private:
    Container* mContainer = nullptr;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
