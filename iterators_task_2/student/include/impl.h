#pragma once
#include <iterator>

// https://ideone.com/Vp22H3
template <class Container>
struct accumulator : std::iterator<std::output_iterator_tag, void, void, void, void>
{
    /** @todo Iterator traits*/
    /** @todo Constructor with container*/
    /** @todo lvalue writing operator*/
    /** @todo rvalue writing operator*/

    /** @todo Iterator operations */

    accumulator(Container& conatiner) :
        m_container{conatiner}
    {}


    template<class OtherConatianer>
    accumulator& operator =(OtherConatianer&& rhs)
    {
        std::move(rhs.begin(), rhs.end(), std::back_inserter(m_container));
        return *this;

    }

    template<class OtherConatianer>
    accumulator& operator =(const OtherConatianer& rhs)
    {
        std::copy(rhs.begin(), rhs.end(), std::back_inserter(m_container));
        return *this;
    }

    accumulator& operator *() { return *this; }

    accumulator& operator ++() { return *this; }

    accumulator operator ++(int) { return *this; }

private:
    Container& m_container;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    accumulator<Container> accumulator{container};
    return accumulator;
}
