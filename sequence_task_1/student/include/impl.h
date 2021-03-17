#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class StaticPlaylist
{
public:
    /** Member traits */
    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using difference_type = typename Container::difference_type;
    using size_type = typename Container::size_type;
    using self_type = StaticPlaylist<Container, Song_t>;

    /** Iterators */
    const_iterator begin() const {
        return m_tracklist.cbegin();
    }

    const_iterator end() const {
        return m_tracklist.cend();
    }

    StaticPlaylist() = default;
    StaticPlaylist(const self_type& other) = default;
    StaticPlaylist(self_type&& other) = default;
    self_type& operator=(const self_type& rhs) = default;
    self_type& operator=(self_type&& rhs) = default;

    /** Constructor from any reversible sequence container */
    template <class AnyContainer>
    StaticPlaylist(const AnyContainer& container)
        : m_tracklist(container.rbegin(), container.rend())
    {}

    /** Assignment from any reversible sequence container */
    template <class AnyContainer>
    StaticPlaylist<Container, Song_t>& operator=(const AnyContainer& container)
    {
        m_tracklist.assign(container.rbegin(), container.rend());
        return *this;
    }

    /** Add track from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData)
    {
        m_tracklist.emplace_back(std::forward<Args>(songData)...);
        return current();
    }

    /** Add track */
    const Song_t& play(const Song_t& song)
    {
        m_tracklist.push_back(song);
        return current();
    }

    /** Get first track in playlist stack */
    const Song_t& current() const
    {
        return m_tracklist.back();
    }

    /** Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if (!hasTracks()) {
            throw std::out_of_range("switchNext");
        }
        m_tracklist.pop_back();
    }

    /** Amount of tracks in playlist */
    size_type count() const
    {
        return m_tracklist.size();
    }

    /** Checks if playlist has any playable tracks */
    bool hasTracks() const
    {
        return count() > 0;
    }

private:
    Container m_tracklist;
};
