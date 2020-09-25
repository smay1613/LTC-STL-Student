#pragma once
#include <iterator>
#include <deque>
#include <vector>

template <class Container>
struct accumulator 
{
private:
    Container& mContainer;
public:
    /** @todo Iterator traits*/
    using iterator_category = std::output_iterator_tag;
    using value_type =  typename Container::value_type;
    using difference_type = typename Container::difference_type;
    using pointer = typename Container::pointer;
    using reference = typename Container::reference;
    
    /** @todo Constructor with container*/
    explicit accumulator(Container & container)
    : mContainer (container)
    {

    }

    /** @todo Copy assignment operator*/
    accumulator& operator=(const value_type& value)
    {
	    mContainer.push_back(value);
	    return *this;
    }
    
    /** @todo Move assignment operator*/
    accumulator& operator=(value_type&& value)
    {
        mContainer.push_back(std::move(value));
        return *this;
    }

    accumulator& operator=(const std::string& value)
    {
	    for (auto && item: value)
        {
            mContainer.push_back(item);
        }
        return *this;
    }

    accumulator& operator=(std::string&& value)
    {
        for (auto && item: value)
        {
            mContainer.push_back(std::move(item));
        }
        
        return *this;
    }

    accumulator& operator=(const std::deque<value_type>& value)
    {
        for (auto && item: value)
        {
            mContainer.push_back(item);
        }
        
        return *this;
    }

    accumulator& operator=(std::deque<value_type>&& value)
    {
        for (auto && item: value)
        {
            mContainer.push_back(std::move(item));
        }
        
        return *this;
    }

    accumulator& operator=(const std::vector<value_type>& value)
    {
        for (auto && item: value)
        {
            mContainer.push_back(item);
        }
        
        return *this;
    }

    accumulator& operator=(std::vector<value_type>&& value)
    {
        for (auto && item: value)
        {
            mContainer.push_back(std::move(item));
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
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
inline accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
