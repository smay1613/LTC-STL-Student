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
    public:
        /** @todo Iterator traits */
        using value_type = const std::string;
        using reference = typename Iterator::reference;
        using pointer = typename Iterator::pointer;
        using iterator_category = typename Iterator::iterator_category;
        using difference_type = typename Iterator::difference_type;

        /** @todo Iterator operations */
        pair_iterator& operator++()
        {
            m_iter++;
            return *this;
        }

        pair_iterator& operator--()
        {
            m_iter--;
            return *this;
        }

        value_type& operator*()
        {
            return m_iter->first;
        }

        template<typename _T>
        void operator=(const _T& val) = delete;
        
        operator value_type()
        {
            return m_iter->first;
        }

        /** @todo Constructor from original iterator */
        pair_iterator() = default;

        pair_iterator(Iterator it)
            : m_iter(it)
        {}

    private:
        Iterator m_iter;
};

/**
 * @todo Implement iterator for pair value type
 */
template<class Iterator, class T>
struct pair_iterator<Iterator, false, T> : public Iterator
{
    public:
        /** @todo Iterator traits */
        using value_type = size_t;
        using reference = typename Iterator::reference;
        using pointer = typename Iterator::pointer;
        using iterator_category = typename Iterator::iterator_category;
        using difference_type = typename Iterator::difference_type;

        /** @todo Iterator operations */
        pair_iterator& operator++()
        {
            m_iter++;
            return *this;
        }

        pair_iterator& operator++(int)
        {
            m_iter++;
            return *this;
        }

        pair_iterator& operator--()
        {
            m_iter--;
            return *this;
        }

        pair_iterator& operator--(int)
        {
            m_iter--;
            return *this;
        }

        template<typename _T>
        void operator=(_T& val)
        {
            m_iter->second = val;
        }

        operator value_type()
        {
            return m_iter->second;
        }

        /** @todo Constructor from original iterator */
        pair_iterator() = default;

        pair_iterator(Iterator it)
            : m_iter(it)
        {}

    private:
        Iterator m_iter;
};

template<class Iterator>
using key_iterator = pair_iterator<Iterator, true>;

template<class Iterator>
using value_iterator = pair_iterator<Iterator, false>;

/** @todo Value iterator generator */
template <class MapIterator>
value_iterator<MapIterator> make_value_iterator (MapIterator iterator)
{
    return value_iterator<MapIterator>(iterator);
};

/** @todo Key iterator generator */
template <class MapIterator>
key_iterator<MapIterator> make_key_iterator (MapIterator iterator)
{
    return key_iterator<MapIterator>(iterator);
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
    using iterator = key_iterator<typename Map::iterator>;
    using const_iterator = key_iterator<typename Map::const_iterator>;
    using base_map_view<Map>::base_map_view;

    /** @todo begin/end iterators */
    iterator begin()
    {
        return make_key_iterator<iterator>(m_map.begin());
    }

    iterator end()
    {
        return make_key_iterator<iterator>(m_map.end());
    }

    const_iterator begin() const
    {
        return make_key_iterator<const_iterator>(m_map.begin());
    }

    const_iterator end() const
    {
        return make_key_iterator<const_iterator>(m_map.end());
    }

private:
    using base_map_view<Map>::m_map;
};

template<class Map>
struct map_values_view : public base_map_view<Map>
{
    /** @todo Iterator alias */
    using iterator = value_iterator<typename Map::iterator>;
    using base_map_view<Map>::base_map_view;

    /** @todo begin/end iterators */
    iterator begin()
    {
        return make_value_iterator<iterator>(m_map.begin());
    }

    iterator end()
    {
        return make_value_iterator<iterator>(m_map.end());
    }

    iterator begin() const
    {
        return make_value_iterator<iterator>(m_map.begin());
    }

    iterator end() const
    {
        return make_value_iterator<iterator>(m_map.end());
    }

private:
    using base_map_view<Map>::m_map;
};

/** @todo Generator for values view*/
template <class Map>
map_values_view<Map> make_values_view(Map& map)
{
    return map_values_view<Map>(map);
}

/**  @todo Generator for keys view*/
template <class Map>
map_keys_view<Map> make_keys_view(Map& map)
{
    return map_keys_view<Map>(map);
}

/**  @todo Generator for const values view*/
template <class Map>
const map_values_view<const Map> make_values_view(const Map& map)
{
    return map_values_view<const Map>(map);
}

/**  @todo Generator for const keys view*/
template <class Map>
const map_keys_view<const Map> make_keys_view(const Map& map)
{
    return map_keys_view<const Map>(map);
}
