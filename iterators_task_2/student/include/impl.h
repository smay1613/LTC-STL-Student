#pragma once
#include <iterator>

template <class Container>
struct accumulator : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
    /** @todo Iterator traits*/
    /** @todo Constructor with container*/
    /** @todo lvalue writing operator*/
    /** @todo rvalue writing operator*/

    /** @todo Iterator operations */

    protected:
        Container* container;
    public:
        explicit accumulator(Container& __x) : container(&__x){}

        template<typename Input>
        accumulator& operator=(const Input& __value) {
            std::copy(__value.cbegin(), __value.cend(), std::back_inserter(*container));
            return *this;
        }

        template<typename Input>
        accumulator& operator=(Input&& __value) {
            std::move(__value.begin(), __value.end(), std::back_inserter(*container));
            return *this;
        }

        accumulator& operator*() { return *this; }
        accumulator& operator++() { return *this; }
        accumulator operator++(int) { return *this; }
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>{container};
}
