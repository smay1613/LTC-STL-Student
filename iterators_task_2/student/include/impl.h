#pragma once
#include <iterator>
#include <deque>

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
    explicit accumulator(Container& con): container(&con) {};

    accumulator& operator=(Container& conLR) {
        container->insert(container->end(), conLR.begin(), conLR.end());
        return *this;
    }

    accumulator& operator=(Container&& conRR) {
        container->insert(container->end(),
                          std::make_move_iterator(conRR.begin()),
                          std::make_move_iterator(conRR.end()));
        return *this;
    }

    accumulator& operator=(const std::deque<typename Container::value_type>& decqu) {
        container->insert(container->end(), decqu.begin(), decqu.end());
        return *this;
    }

    accumulator& operator=(const typename Container::value_type& value) {
        container->insert(container->end(), value);
        return *this;
    }
    accumulator& operator=(typename Container::value_type&& value) {
        container->insert(container->end(), std::move(value));
        return *this;
    }
    accumulator& operator*() { return *this; }
    accumulator& operator++() { return *this; }
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
