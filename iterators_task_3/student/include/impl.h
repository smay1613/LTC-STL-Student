#pragma once
#include <map>
#include <iterator>
#include <type_traits>

template <class Iterator, bool IsFirst, class T = typename std::iterator_traits<Iterator>::value_type>
struct pair_iterator : public Iterator
{
};

/**
 * @todo Implement iterator for pair key type
 */
template<class Iterator, class T>
struct pair_iterator<Iterator, true, T> : public Iterator
{
    /** @todo Iterator traits */
    /** @todo Iterator operations */
    /** @todo Constructor from original iterator */
};

/**
 * @todo Implement iterator for pair value type
 */
template<class Iterator, class T>
struct pair_iterator<Iterator, false, T> : public Iterator
{
    /** @todo Iterator traits */
    /** @todo Iterator operations */
    /** @todo Constructor from original iterator */
};

template<class Iterator>
using key_iterator = pair_iterator<Iterator, true>;

template<class Iterator>
using value_iterator = pair_iterator<Iterator, false>;

/** @todo Value iterator generator */
template <class MapIterator>
value_iterator<MapIterator> make_value_iterator (MapIterator iterator)
{
};

/** @todo Key iterator generator */
template <class MapIterator>
key_iterator<MapIterator> make_key_iterator (MapIterator iterator)
{
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
    /** @todo Iterator alias */

    using base_map_view<Map>::base_map_view;

    /** @todo begin/end iterators */
private:
    using base_map_view<Map>::m_map;
};

template<class Map>
struct map_values_view : public base_map_view<Map>
{
    /** @todo Iterator alias */

    using base_map_view<Map>::base_map_view;

    /** @todo begin/end iterators */
private:
    using base_map_view<Map>::m_map;
};

/** @todo Generator for values view*/
template <class Map>
map_values_view<Map> make_values_view(Map& map)
{
}

/**  @todo Generator for keys view*/
template <class Map>
map_keys_view<Map> make_keys_view(Map& map)
{
}

/**  @todo Generator for const values view*/
template <class Map>
const map_values_view<const Map> make_values_view(const Map& map)
{
}

/**  @todo Generator for const keys view*/
template <class Map>
const map_keys_view<const Map> make_keys_view(const Map& map)
{
}
