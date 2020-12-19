#pragma once
#include <string>
#include <memory>
#include <algorithm>

struct Song
{
    std::string name;
    explicit Song(std::string song_name)
        : name {std::move(song_name)}
    {
    }
};

bool operator==(const Song& lhs, const Song& rhs)
{
    return lhs.name == rhs.name;
}

template<class Container>
class StaticPlaylist
{
public:
    /** @todo Member traits */
    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using pointer = typename Container::pointer;
    using const_pointer = typename Container::const_pointer;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using difference_type = typename Container::difference_type;
    using size_type = typename Container::size_type;//size_t;
    using reverse_iterator = typename Container::reverse_iterator;//std::reverse_iterator<iterator>;
    using const_reverse_iterator = typename Container::const_reverse_iterator;//std::reverse_iterator<const_iterator>;

    /** @todo Iterators */
    /**
     *  Returns a read-only (constant) iterator that points to the
     *  first element in the %underlying container.  Iteration is done in ordinary
     *  element order.
     */
    const_iterator
    begin() const _GLIBCXX_NOEXCEPT
    {
        //return const_iterator(this->m_tracklist.cbegin());
        return m_tracklist.begin();
    }

    /**
     *  Returns a read-only (constant) iterator that points one past
     *  the last element in the %underlying container.  Iteration is done in
     *  ordinary element order.
     */
    const_iterator
    end() const _GLIBCXX_NOEXCEPT
    {
        //return const_iterator(this->m_tracklist.cend());
        m_tracklist.end();
    }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to the last element in the %underlying container.  Iteration is done in
     *  reverse element order.
     */
    const_reverse_iterator
    rbegin() const _GLIBCXX_NOEXCEPT
    {
        //return const_reverse_iterator(end());
        return m_tracklist.rbegin();
    }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to one before the first element in the %underlying container.  Iteration
     *  is done in reverse element order.
     */
    const_reverse_iterator
    rend() const _GLIBCXX_NOEXCEPT
    {
        //return const_reverse_iterator(begin());
        return m_tracklist.rend();
    }

#if __cplusplus >= 201103L
    /**
     *  Returns a read-only (constant) iterator that points to the
     *  first element in the %underlying container.  Iteration is done in ordinary
     *  element order.
     */
    const_iterator
    cbegin() const noexcept
    {
        //return const_iterator(this->m_tracklist.cbegin());
        return m_tracklist.cbegin();
    }

    /**
     *  Returns a read-only (constant) iterator that points one past
     *  the last element in the %underlying container.  Iteration is done in
     *  ordinary element order.
     */
    const_iterator
    cend() const noexcept
    {
        //return const_iterator(this->m_tracklist.cend());
        return m_tracklist.cend();
    }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to the last element in the %underlying container.  Iteration is done in
     *  reverse element order.
     */
    const_reverse_iterator
    crbegin() const noexcept
    {
        //return const_reverse_iterator(end());
        return m_tracklist.crbegin();
    }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to one before the first element in the %underlying container.  Iteration
     *  is done in reverse element order.
     */
    const_reverse_iterator
    crend() const noexcept
    {
        //return const_reverse_iterator(begin());
        return m_tracklist.crend();
    }
#endif

    /** @todo Constructor from any reversible sequence container */
    /**
     *  @brief  Creates a %underlying container with no elements.
     */
    StaticPlaylist() = default;

    template<class T>
    StaticPlaylist(std::initializer_list<T>& __l) : m_tracklist({__l.crbegin(), __l.crend()})
    {}

    /**
     *  @brief  %StaticPlaylist copy constructor.
     *  @param  __x  A %StaticPlaylist of identical element.
     */
    template<class T>
    StaticPlaylist(const T& __x)
    {
        m_tracklist.assign(__x.rbegin(), __x.rend());
    }

#if __cplusplus >= 201103L
    /**
     *  @brief  %StaticPlaylist move constructor.
     */
    StaticPlaylist(Container&& __x)
    : m_tracklist(/*std::forward(__x)*/__x)
    {
        std::reverse(m_tracklist.begin(), m_tracklist.end());
    }
#endif

    /**
     *  @brief  Builds a %StaticPlaylist from a range.
     *  @param  __first  An input iterator.
     *  @param  __last  An input iterator.
     */
#if __cplusplus >= 201103L
    template<typename _InputIterator,
         typename = std::_RequireInputIter<_InputIterator>>
    StaticPlaylist(_InputIterator __first, _InputIterator __last)
    {
        m_tracklist({__first, __last});
        std::reverse(m_tracklist.begin(), m_tracklist.end());
    }
#else
    template<typename _InputIterator>
    StaticPlaylist(_InputIterator __first, _InputIterator __last)
    {
        // Check whether it's an integral type.  If so, it's not an iterator.
        typedef typename std::__is_integer<_InputIterator>::__type _Integral;
        m_tracklist(__first, __last);
        std::reverse(m_tracklist.begin(), m_tracklist.end());
    }
#endif

    /** @todo Assignment from any reversible sequence container */
    /**
     *  @brief  %StaticPlaylist assignment operator.
     */
      template<class T>
      StaticPlaylist&
      operator=(const T& __x)
      {
          m_tracklist.assign(__x.crbegin(), __x.crend());
          return *this;
      }

    /**
     *  @brief  %StaticPlaylist move assignment operator.
     */
      StaticPlaylist&
      operator=(Container&& __x)
      {
          m_tracklist(std::move(__x));
          std::reverse(m_tracklist.begin(), m_tracklist.end());
          return *this;
      }

    /**
     *  @brief  %StaticPlaylist list assignment operator.
     *  @param  __l  An initializer_list.
     */
      StaticPlaylist&
      operator=(std::initializer_list<value_type> __l)
      {
          m_tracklist.assign(__l.begin(), __l.end());
          return *this;
      }

    /** @todo Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData)
    {
        m_tracklist.emplace_back(std::forward<Args>(songData)...);
        return current();
    }

    /** @todo Add track */
    const Song& play(const Song& song)
    {
        m_tracklist.push_back(song);
        return current();
    }

    /** @todo Get first track in playlist stack */
    const Song& current() const
    {
        return m_tracklist.back();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if(!m_tracklist.empty()) {
            m_tracklist.erase(prev(m_tracklist.end()));
        } else {
            throw std::out_of_range("error");
        }
    }

    /** @todo Amount of tracks in playlist */
    size_type count() const
    {
        return m_tracklist.size();
    }

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const
    {
        return !m_tracklist.empty();
    }

private:
    Container m_tracklist;
};
