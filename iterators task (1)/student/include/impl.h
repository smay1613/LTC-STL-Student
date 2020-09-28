#pragma once
#include <iterator>

template <class Container>
struct accumulator
{
    /** @todo Iterator traits*/
    using traits = std::iterator_traits<typename Container::iterator>;
    using difference_type = typename traits::difference_type;
    using value_type = void;
    using pointer = void;
    using reference = void;
    using iterator_category = std::output_iterator_tag;

    /** @todo Constructor with container*/
    accumulator<Container>(Container& container)
        : container_{container}
    {
    }
    accumulator<Container>(const accumulator<Container>& c) = default;
    accumulator<Container>(accumulator<Container>&& c) = default;

    /** @todo Copy assignment operator*/
    template <class Input>
    accumulator<Container>& operator =(const Input& inputData)
    {
        std::copy(inputData.begin(),
                  inputData.end(),
                  std::back_inserter(container_));
        return *this;
    }

    /** @todo Move assignment operator*/
    template <class Input>
    accumulator<Container>& operator =(Input&& inputData)
    {
        std::move(inputData.begin(),
                  inputData.end(),
                  std::back_inserter(container_));
        return *this;
    }

    /** @todo Iterator operations */
    accumulator<Container>& operator*() { return *this; }
    accumulator<Container>& operator++() { return *this; }
private:
    Container& container_;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>(container);
}
