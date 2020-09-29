#pragma once
#include <map>
#include <iterator>
#include <type_traits>

template <class Iterator, bool IsFirst, class T = typename std::iterator_traits<Iterator>::value_type>
struct pair_iterator : public Iterator
{
};

/**
 * iterator for pair key type
 */
template<class Iterator, class T>
struct pair_iterator<Iterator, true, T> : public Iterator
{
    /** Iterator traits */
    using iterator_category = typename Iterator::iterator_category;
    using difference_type = typename Iterator::difference_type;
    
    using value_type = typename T::first_type;
    using pointer = value_type*;
    using reference = value_type&;

    /** Iterator operations */

    reference operator*() const 
    {
        return Iterator::operator*().first;
    }

    pointer operator->() const
    {
        return Iterator::operator->().first;
    }

    /** Constructor from original iterator */
    pair_iterator(Iterator base_iterator) : Iterator(base_iterator)
    {

    }
};

/**
 * @ iterator for pair value type
 */
template<class Iterator, class T>
struct pair_iterator<Iterator, false, T> : public Iterator
{
    /** Iterator traits */

    using iterator_category = typename Iterator::iterator_category;
    using difference_type = typename Iterator::difference_type;
    
    using value_type = typename T::second_type;

    // https://en.cppreference.com/w/cpp/types/is_const
    // if T is a reference type then is_const<T>::value is always false. 
    // The proper way to check a potentially-reference type for const-ness is to remove the reference: is_const<typename remove_reference<T>::type>.
    using pointer = typename std::conditional< 
                                        std::is_const<typename std::remove_reference<typename Iterator::pointer>::type>::value,
                                        const value_type*,
                                        value_type*
                                    >::type ;
    using reference  = typename std::conditional< 
                                         std::is_const<typename std::remove_reference<typename Iterator::reference>::type>::value,
                                         const value_type&,
                                         value_type&
                                      >::type ;

    /** Iterator operations */

    reference operator*() const 
    {
        return Iterator::operator*().second;
    }

    pointer operator->() const
    {
        return Iterator::operator->().second;
    }

    /** Constructor from original iterator */
    pair_iterator(Iterator base_iterator) : Iterator(base_iterator)
    {

    }
};

template<class Iterator>
using key_iterator = pair_iterator<Iterator, true>;

template<class Iterator>
using value_iterator = pair_iterator<Iterator, false>;

template <class MapIterator>
value_iterator<MapIterator> make_value_iterator (MapIterator iterator)
{
    return value_iterator<MapIterator> {iterator};
};

template <class MapIterator>
key_iterator<MapIterator> make_key_iterator (MapIterator iterator)
{
    return key_iterator<MapIterator> {iterator};
};

template<class Map>
struct base_map_view
{
    base_map_view() = delete;
    base_map_view(Map& map) : m_map {map} {}

protected:
    Map& m_map;
};

template<class Map>
struct map_keys_view : public base_map_view<Map>
{
    using iterator = key_iterator<typename Map::iterator>;
    using const_iterator = key_iterator<typename Map::const_iterator>;

    using base_map_view<Map>::base_map_view;

    iterator begin()
    {
        return make_key_iterator(m_map.begin());
    }
    iterator end()
    {
        return make_key_iterator(m_map.end());
    }
    const_iterator begin() const
    {
        return make_key_iterator(m_map.cbegin());
    }
    const_iterator end() const
    {
        return make_key_iterator(m_map.cend());
    }
private:
    using base_map_view<Map>::m_map;
};

template<class Map>
struct map_values_view : public base_map_view<Map>
{
    using iterator = value_iterator<typename Map::iterator>;
    using const_iterator = value_iterator<typename Map::const_iterator>;

    using base_map_view<Map>::base_map_view;

    iterator begin()
    {
        return make_value_iterator(m_map.begin());
    }
    iterator end()
    {
        return make_value_iterator(m_map.end());
    }
    const_iterator begin() const
    {
        return make_value_iterator(m_map.cbegin());
    }
    const_iterator end() const
    {
        return make_value_iterator(m_map.cend());
    }
private:
    using base_map_view<Map>::m_map;
};

/** Generator for values view*/
template <class Map>
map_values_view<Map> make_values_view(Map& map)
{
    return map_values_view<Map> {map};
}

/**  Generator for keys view*/
template <class Map>
map_keys_view<Map> make_keys_view(Map& map)
{
    return map_keys_view<Map> {map};
}

/**  Generator for const values view*/
template <class Map>
const map_values_view<const Map> make_values_view(const Map& map)
{
    return map_values_view<const Map> {map};
}

/**  Generator for const keys view*/
template <class Map>
const map_keys_view<const Map> make_keys_view(const Map& map)
{
    return map_keys_view<const Map> {map};
}
