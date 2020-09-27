#pragma once
#include <iterator>

template < class Container >
struct accumulator
{
    /** @todo Iterator traits */
    using ContainerTraits = std::iterator_traits< typename Container::iterator >;
    using iterator_category = std::output_iterator_tag;
    using value_type = typename ContainerTraits::value_type;
    using difference_type = typename ContainerTraits::difference_type;
    using pointer = typename ContainerTraits::pointer;
    using reference = typename Container::reference;

    /** @todo Constructor with container */
    accumulator( Container& c )
        : m_container{c}
    {
    }

    accumulator( accumulator< Container > const& c ) = default;
    accumulator( accumulator< Container >&& c ) = default;

    /** @todo Copy assignment operator */
    template < typename OtherContainer >
    accumulator< Container >&
    operator=( OtherContainer const& c )
    {
        std::copy( std::begin( c ), std::end( c ), std::back_inserter( m_container ) );
        return *this;
    };

    /** @todo Move assignment operator */
    template < typename OtherContainer >
    accumulator< Container >&
    operator=( OtherContainer&& c )
    {
        std::move( std::begin( c ), std::end( c ), std::back_inserter( m_container ) );
        return *this;
    };

    /** @todo Iterator operations */
    accumulator< Container >&
    operator++( )
    {
        return *this;
    }

    accumulator< Container >& operator*( )
    {
        return *this;
    }

public:
    Container& m_container;
};

/**
 *  @todo Implement accumulator object creator
 */
template < class Container >
accumulator< Container >
make_accumulator( Container& container )
{
    return accumulator< Container >( container );
}
