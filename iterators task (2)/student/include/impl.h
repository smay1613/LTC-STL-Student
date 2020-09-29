#pragma once

#include <map>
#include <iterator>
#include <type_traits>
#include <utility>

template <class FromRefType, class ToRefType>
struct copy_reference_constness
{
    using type =
        typename std::conditional<
            std::is_const<typename std::remove_reference<FromRefType>::type>::value,
            const typename std::remove_reference<ToRefType>::type&,
            ToRefType
        >::type;
};

template <class Iterator, bool IsFirst, class T = typename std::iterator_traits<Iterator>::value_type>
struct pair_iterator : public Iterator
{
};

template<class Iterator, class T>
struct pair_iterator<Iterator, true, T> : public Iterator
{
    using value_type = typename T::first_type;
    using reference = typename copy_reference_constness<typename std::iterator_traits<Iterator>::reference,
                                                        value_type&>::type;
    using pointer = typename std::add_pointer<reference>::type;

    explicit pair_iterator(Iterator iterator) : Iterator(iterator) {}

    reference operator*()
    {
        return (*this)->first;
    }
};

template<class Iterator, class T>
struct pair_iterator<Iterator, false, T> : public Iterator
{
    using value_type = typename T::second_type;
    using reference = typename copy_reference_constness<typename std::iterator_traits<Iterator>::reference,
                                                        value_type&>::type;
    using pointer = typename std::add_pointer<reference>::type;

    explicit pair_iterator(Iterator iterator) : Iterator(iterator) {}

    reference operator*()
    {
        return (*this)->second;
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
