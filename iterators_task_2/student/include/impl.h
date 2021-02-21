#pragma once
#include <iterator>

// https://ideone.com/Vp22H3
template <class Container>
struct accumulator
{
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::output_iterator_tag;
    /** @todo Iterator traits*/
    /** @todo Constructor with container*/
    /** @todo lvalue writing operator*/
    /** @todo rvalue writing operator*/

    /** @todo Iterator operations */

    accumulator(Container conatiner) :
        m_container{conatiner}
    {}

private:
    Container m_container;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
}
