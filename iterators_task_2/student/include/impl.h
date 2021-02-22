#pragma once
#include <iterator>

template <class Container>
struct accumulator:public std::iterator<std::output_iterator_tag, void,void,void,void>
{
    private:
        Container &m_container;
    public:
        explicit accumulator(Container&__x):m_container(__x){};

template <typename other>
    accumulator& operator=(const other&__value){
        std::copy(__value.cbegin(), __value.cend(), std::back_inserter(m_container));
        return *this;
    }

    template <typename other>
    accumulator& operator=( other&&__value){
        std::move(__value.begin(), __value.end(), std::back_inserter(m_container));
        return *this;
    }
    accumulator& operator++(){
        return *this;
    }

    accumulator operator++(int){
            return *this;
        }

    accumulator& operator*(){
            return *this;
        }
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
   return accumulator<Container>(container);
}
