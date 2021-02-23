#pragma once
#include <map>
#include <iterator>
#include <type_traits>

template <class Iterator, bool IsFirst, class Traits = typename std::iterator_traits<Iterator>>
struct pair_iterator : public Iterator
{
};

template<class Iterator, class Traits>
struct pair_iterator<Iterator, true, Traits> : public Iterator
{
    using iterator_category = typename Traits::iterator_category;
    using value_type = const typename Traits::value_type::first_type;
    using reference = value_type&;
    using pointer = value_type*;
    using difference_type = typename Traits::difference_type;

    template<typename It>
    pair_iterator(It&& it) : Iterator{std::forward<It>(it)} {}

    pair_iterator& operator++() {
        Iterator& tmp = *this;
        ++tmp;
        return *this;
    }

    pair_iterator operator++(int) {
        Iterator tmp = *this;
        *this++;
        return tmp;
    }

    pair_iterator& operator--() {
        Iterator& tmp = *this;
        --tmp;
        return *this;
    }

    pair_iterator operator--(int) {
        Iterator tmp = *this;
        *this--;
        return tmp;
    }

    reference operator*() const {
        return (*this)->first;
    }

};

template<class Iterator, class Traits>
struct pair_iterator<Iterator, false, Traits> : public Iterator
{
    using iterator_category = typename Traits::iterator_category;

    using Val = typename Traits::value_type;
    using IsConstVal = typename std::is_const<Val>;
    using value_type = typename std::conditional<IsConstVal::value,
                                                 const typename Val::second_type,
                                                 typename Val::second_type
                                                >::type;

    using Ref = typename std::iterator_traits<Iterator>::reference;
    using IsConstRef = typename std::is_const<typename std::remove_reference<Ref>::type>;
    using reference = typename std::conditional<IsConstRef::value,
                                                const typename Val::second_type&,
                                                typename Val::second_type&
                                               >::type;

    using pointer = value_type*;
    using difference_type = typename Traits::difference_type;

    template<typename It>
    pair_iterator(It&& it) : Iterator{std::forward<It>(it)} {}

    pair_iterator& operator++() {
        Iterator& tmp = *this;
        ++tmp;
        return *this;
    }

    pair_iterator operator++(int) {
        Iterator tmp = *this;
        *this++;
        return tmp;
    }

    pair_iterator& operator--() {
        Iterator& tmp = *this;
        --tmp;
        return *this;
    }

    pair_iterator operator--(int) {
        Iterator tmp = *this;
        *this--;
        return tmp;
    }

    reference operator*() const {
        return (*this)->second;
    }
};

template<class Iterator>
using key_iterator = pair_iterator<Iterator, true>;

template<class Iterator>
using value_iterator = pair_iterator<Iterator, false>;

template <class MapIterator>
value_iterator<MapIterator> make_value_iterator (MapIterator&& iterator)
{
    return value_iterator<MapIterator>(std::forward<MapIterator>(iterator));
};

template <class MapIterator>
key_iterator<MapIterator> make_key_iterator (MapIterator&& iterator)
{
    return key_iterator<MapIterator>(std::forward<MapIterator>(iterator));
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
    using const_key_iterator = ::key_iterator<typename Map::const_iterator>;
    using base_map_view<Map>::base_map_view;

    const_key_iterator begin() const
    {
        return make_key_iterator(m_map.cbegin());
    }

    const_key_iterator end() const
    {
        return make_key_iterator(m_map.cend());
    }

    const_key_iterator cbegin() const
    {
        return make_key_iterator(m_map.cbegin());
    }

    const_key_iterator cend() const
    {
        return make_key_iterator(m_map.cend());
    }

private:
    using base_map_view<Map>::m_map;
};

template<class Map>
struct map_values_view : public base_map_view<Map>
{
    using value_iterator = ::value_iterator<typename Map::iterator>;
    using const_value_iterator = ::value_iterator<typename Map::const_iterator>;
    using base_map_view<Map>::base_map_view;

    value_iterator begin()
    {
        return make_value_iterator(m_map.begin());
    }

    value_iterator end()
    {
        return make_value_iterator(m_map.end());
    }

    const_value_iterator begin() const
    {
        return make_value_iterator(m_map.cbegin());
    }

    const_value_iterator end() const
    {
        return make_value_iterator(m_map.cend());
    }

    const_value_iterator cbegin() const
    {
        return make_value_iterator(m_map.cbegin());
    }

    const_value_iterator cend() const
    {
        return make_value_iterator(m_map.cend());
    }

private:
    using base_map_view<Map>::m_map;
};

template <class Map>
map_values_view<Map> make_values_view(Map& map)
{
    return map_values_view<Map>(map);
}

template <class Map>
map_keys_view<Map> make_keys_view(Map& map)
{
    return map_keys_view<Map>(map);
}

template <class Map>
const map_values_view<const Map> make_values_view(const Map& map)
{
    return map_values_view<const Map>(map);
}

template <class Map>
const map_keys_view<const Map> make_keys_view(const Map& map)
{
    return map_keys_view<const Map>(map);
}
