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
    Container &container;
public:
    explicit accumulator(Container& con): container(con) {};

    // ??? If I would like to specify the same value_type for another container. Is it correct?
//    template< template<class> class another_cont>
//    accumulator& operator=(const another_cont<typename Container::value_type>& another) {
//        container.insert(container.end(), another.begin(), another.end());
//        return *this;
//    }

    template<class another_cont>
    accumulator& operator=(another_cont& another) {
        container.insert(container.end(), another.begin(), another.end());
        return *this;
    }

    template<class another_cont>
    accumulator& operator=(another_cont&& another) {
        container.insert(container.end(),
                          std::make_move_iterator(another.begin()),
                          std::make_move_iterator(another.end()));
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
