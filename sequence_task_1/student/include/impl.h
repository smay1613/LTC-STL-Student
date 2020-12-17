#pragma once
#include <string>

#if __cplusplus >= 201103L
#include <initializer_list>
#endif

#include <memory>

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
    using iterator = __gnu_cxx::__normal_iterator<pointer, Container>;
    using const_iterator = __gnu_cxx::__normal_iterator<const_pointer, Container>;
    using difference_type = typename Container::difference_type/*ptrdiff_t*/;
    using size_type = size_t;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /** @todo Iterators */
    /**
     *  Returns a read-only (constant) iterator that points to the
     *  first element in the %vector.  Iteration is done in ordinary
     *  element order.
     */
    const_iterator
    begin() const _GLIBCXX_NOEXCEPT
    { return const_iterator(this->m_tracklist.cbegin()); }

    /**
     *  Returns a read-only (constant) iterator that points one past
     *  the last element in the %vector.  Iteration is done in
     *  ordinary element order.
     */
    const_iterator
    end() const _GLIBCXX_NOEXCEPT
    { return const_iterator(this->m_tracklist.cend()); }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to the last element in the %vector.  Iteration is done in
     *  reverse element order.
     */
    const_reverse_iterator
    rbegin() const _GLIBCXX_NOEXCEPT
    { return const_reverse_iterator(end()); }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to one before the first element in the %vector.  Iteration
     *  is done in reverse element order.
     */
    const_reverse_iterator
    rend() const _GLIBCXX_NOEXCEPT
    { return const_reverse_iterator(begin()); }

#if __cplusplus >= 201103L
    /**
     *  Returns a read-only (constant) iterator that points to the
     *  first element in the %vector.  Iteration is done in ordinary
     *  element order.
     */
    const_iterator
    cbegin() const noexcept
    { return const_iterator(this->m_tracklist.cbegin()); }

    /**
     *  Returns a read-only (constant) iterator that points one past
     *  the last element in the %vector.  Iteration is done in
     *  ordinary element order.
     */
    const_iterator
    cend() const noexcept
    { return const_iterator(this->m_tracklist.cend()); }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to the last element in the %vector.  Iteration is done in
     *  reverse element order.
     */
    const_reverse_iterator
    crbegin() const noexcept
    { return const_reverse_iterator(end()); }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to one before the first element in the %vector.  Iteration
     *  is done in reverse element order.
     */
    const_reverse_iterator
    crend() const noexcept
    { return const_reverse_iterator(begin()); }
#endif

    /** @todo Constructor from any reversible sequence container */
    /**
     *  @brief  Creates a %vector with no elements.
     */
    StaticPlaylist()
    {
        m_tracklist();
    }

    template<class T>
    StaticPlaylist(std::initializer_list<T>& __l)
    {
        for(const T& i: __l) {
            m_tracklist.push_back(i);
        }
    }

    /**
     *  @brief  %StaticPlaylist copy constructor.
     *  @param  __x  A %StaticPlaylist of identical element.
     */
    template<class T>
    StaticPlaylist(const T& __x)
    {
        for(typename T::const_iterator i = __x.begin(); i != __x.end(); ++i) {
            m_tracklist.push_back(*i);
        }
    }

#if __cplusplus >= 201103L
    /**
     *  @brief  %StaticPlaylist move constructor.
     */
    StaticPlaylist(Container&& __x)
    : m_tracklist(std::forward(__x)) { }

    /**
     *  @brief  Builds a %StaticPlaylist from an initializer list.
     *  @param  __l  An initializer_list.
     */
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
        m_tracklist(__first, __last);
    }
#else
    template<typename _InputIterator>
    vector(_InputIterator __first, _InputIterator __last)
    {
        // Check whether it's an integral type.  If so, it's not an iterator.
        typedef typename std::__is_integer<_InputIterator>::__type _Integral;
        m_tracklist(__first, __last);
    }
#endif

    /**
     *  The dtor only erases the elements, and note that if the
     *  elements themselves are pointers, the pointed-to memory is
     *  not touched in any way.  Managing the pointer is the user's
     *  responsibility.
     */
    ~StaticPlaylist() _GLIBCXX_NOEXCEPT
    {
        std::_Destroy(this->m_tracklist.begin(), this->m_tracklist.end());
    }

    /** @todo Assignment from any reversible sequence container */
    /**
     *  @brief  %StaticPlaylist assignment operator.
     */
      template<class T>
      StaticPlaylist&
      operator=(const T& __x)
      {
          m_tracklist.assign(__x.cbegin(), __x.cend());
          return *this;
      }

    /**
     *  @brief  %StaticPlaylist move assignment operator.
     */
      StaticPlaylist&
      operator=(Container&& __x)
      {
          m_tracklist(std::move(__x));
          return *this;
      }

    /**
     *  @brief  %StaticPlaylist list assignment operator.
     *  @param  __l  An initializer_list.
     */
      StaticPlaylist&
      operator=(std::initializer_list<value_type> __l)
      {
          m_tracklist.assign(__l);
          return *this;
      }

    /** @todo Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData)
    {
        m_tracklist.emplace_back(std::forward<Args>(songData)...);
        std::iter_swap(m_tracklist.begin(), prev(m_tracklist.end()));
        return current();
    }

    /** @todo Add track */
    const Song& play(const Song& song)
    {
        m_tracklist.push_back(song);
        std::iter_swap(m_tracklist.begin(), prev(m_tracklist.end()));
        return current();
    }

    /** @todo Get first track in playlist stack */
    const Song& current() const
    {
        return m_tracklist.at(0);
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if(!m_tracklist.empty()) {
            m_tracklist.erase(m_tracklist.begin());
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
