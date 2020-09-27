#pragma once
#include <iterator>

template <class Container>
struct accumulator
{
    /** @todo Iterator traits*/
    using ContainerTraits = std::iterator_traits<typename Container::iterator>;
    using iterator_category = std::output_iterator_tag;
    using value_type = typename ContainerTraits::value_type;
    using difference_type = typename ContainerTraits::difference_type;
    using pointer = typename ContainerTraits::pointer;
    using reference = typename ContainerTraits::reference;

    /** @todo Constructor with container*/
    accumulator(Container& container)
        : mContainer(container)
    {};

    /** @todo Copy assignment operator*/
    template<class Source>
    accumulator& operator=(const Source& other)
    {
        std::copy(other.begin(), other.end(), std::back_inserter(mContainer));
        return *this;
    }

    /** @todo Move assignment operator*/
    template<class Source>
    accumulator& operator=(Source&& other)
    {
        std::move(other.begin(), other.end(), std::back_inserter(mContainer));
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

private:
    Container& mContainer{};
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
