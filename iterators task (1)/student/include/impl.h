#pragma once
#include <iterator>

template <class Container>
struct accumulator
{
private:
    Container* m_container = nullptr;
public:
    /** @todo Iterator traits*/
    using iterator_category = std::output_iterator_tag;
    using value_type = Container;
    using difference_type = std::ptrdiff_t;
    using pointer = Container*;
    using reference = Container&;

    /** @todo Constructor with container*/
    accumulator<Container>(Container& container)
    {
        m_container = &container;
    }

    /** @todo Copy assignment operator*/
    template<class AnyContainer>
    accumulator<Container>& operator=(AnyContainer const& container)
    {
        m_container->insert(m_container->end(), container.cbegin(), container.cend());
        return *this;
    }

    /** @todo Move assignment operator*/
    template<class AnyContainer>
    accumulator<Container>& operator=(AnyContainer&& container)
    {
        m_container->insert(m_container->end(), std::make_move_iterator(container.begin()), std::make_move_iterator(container.end()));
        return *this;
    }

    /** @todo Iterator operations */
    accumulator<Container>& operator*() { return *this; }
    accumulator<Container>& operator++() { return *this; }
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
