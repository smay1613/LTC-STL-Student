#pragma once
#include <iterator>

template <class Container>
struct accumulator
{
    /** @todo Iterator traits*/
    typedef std::output_iterator_tag            iterator_category;
    typedef typename Container::value_type      value_type;
    typedef typename Container::difference_type difference_type;
    typedef typename Container::pointer         pointer;
    typedef typename Container::reference       reference;

    /** @todo Constructor with container*/
    explicit accumulator(Container& _container )
        :_container_ref(_container)
    {}

    /** @todo Copy assignment operator*/
    accumulator& operator=( const Container& _container)
    {
        _container_ref = _container;
        return *this;
    }

    accumulator& operator=( const reference _value)
    {
        _container_ref.push_back(_value);
        return *this;
    }

    /** @todo Move assignment operator*/
    accumulator& operator=( const Container&& _container )
    {
        _container_ref = std::move(_container);
        return *this;
    }

    template <typename AnotherContainer>
    accumulator& operator=(AnotherContainer&& _container)
    {
        for ( auto&& item_ref: _container)
        {
            _container_ref.push_back(std::move(item_ref));
        }
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
    Container& _container_ref;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
