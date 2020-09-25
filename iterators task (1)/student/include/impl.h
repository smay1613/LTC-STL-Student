#pragma once
#include <iterator>

template <class Container>
struct accumulator 
{
private:
    Container& mContainer;
public:
    /** Iterator traits*/
    using iterator_category = std::output_iterator_tag;
    using value_type =  typename Container::value_type;
    using difference_type = typename Container::difference_type;
    using pointer = typename Container::pointer;
    using reference = typename Container::reference;
    
    /** Constructor with container*/
    explicit accumulator(Container & container)
    : mContainer (container)
    {

    }

    /** Copy assignment operator*/  
    accumulator& operator=(const value_type& value)
    {
	    mContainer.push_back(value);
	    return *this;
    }

    template <typename T>
    accumulator& operator=(const T& value)
    {
        for (auto && item: value)
        {
            mContainer.push_back(item);
        }
        return *this;
    }

    /** Move assignment operator*/
    accumulator& operator=(value_type&& value)
    {
        mContainer.push_back(std::move(value));
        return *this;
    }

    template <typename T>
    accumulator& operator=(T&& value)
    {
        for (auto && item: value)
        {
            mContainer.push_back(std::move(item));
        }
        
        return *this;
    }

    /** Iterator operations */
    accumulator& operator*()
    { 
        return *this; 
    }

    accumulator& operator++()
    { 
        return *this; 
    }
};

/**
 *  accumulator object creator
 */
template<class Container>
inline accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
