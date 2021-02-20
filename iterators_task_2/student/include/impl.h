#pragma once
#include <iterator>

template <class Container>
struct accumulator
        : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
    /** @todo Iterator traits*/
    /** @todo Constructor with container*/
    /** @todo lvalue writing operator*/
    /** @todo rvalue writing operator*/

    /** @todo Iterator operations */
public:
    explicit accumulator(Container& _x) {container = &_x;}

    template<class rhsContainer>
    accumulator<Container>& operator = (rhsContainer&& rhs) {
        std::copy(std::make_move_iterator(rhs.begin()),
                  std::make_move_iterator(rhs.end()),
                  std::back_inserter(*container));
    }

    accumulator& operator = (const typename Container::value_type & _value) {
        container->insert(_value);
        return *this;
    }

    accumulator& operator = (const typename Container::value_type && _value) {
        container->insert(std::move(_value));
        return *this;
    }

    accumulator& operator*() {return *this;}
    accumulator& operator++() {return *this;}
    accumulator operator++(int) {return *this;}

private:
    Container *container;
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
