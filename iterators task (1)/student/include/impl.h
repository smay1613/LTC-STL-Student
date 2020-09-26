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
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    
    /** Constructor with container*/
    explicit accumulator(Container & container)
    : mContainer (container)
    {

    }

    /** Copy assignment operator*/  
    template <typename SourceContainer>
    accumulator& operator=(const SourceContainer& container)
    {
        mContainer.insert(mContainer.end(), container.begin(), container.end());
        return *this;
    }

    /** Move assignment operator*/
    template <typename SourceContainer>
    accumulator& operator=(SourceContainer&& container)
    {
        std::move(container.begin(), container.end(), std::back_inserter(mContainer));        
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
