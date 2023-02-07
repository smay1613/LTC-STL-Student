#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class StaticPlaylist
{
public:
    /** @todo Member traits */
    typedef Song_t value_type;
    typedef Song_t& reference;
    typedef const Song_t& const_reference;
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    /** @todo Iterators */
    const_iterator begin() const
    {
        return m_tracklist.cbegin();
    }

    const_iterator end() const
    {
        return m_tracklist.cend();
    }
    StaticPlaylist() = default;

    /** @todo Constructor from any reversible sequence container */
    template<class GenericContainer>
    StaticPlaylist(const GenericContainer& container)
    {
        m_tracklist.assign(container.rbegin(), container.rend());
    }

    /** @todo Assignment from any reversible sequence container */
    template<class GenericContainer>
    StaticPlaylist<Container, Song_t>& operator=(const GenericContainer& other)
    {
        Container track_list;
        track_list.assign(other.rbegin(), other.rend());

        m_tracklist.swap(track_list);
        return *this;
    }

    /** @todo Add track from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData)
    {
        m_tracklist.emplace(end(), std::forward<Args>(songData)...);
        return current();
    }

    /** @todo Add track */
    const Song_t& play(const Song_t& song)
    {
        m_tracklist.emplace(end(), song);
        return current();
    }

    /** @todo Get first track in playlist stack */
    const Song_t& current() const
    {
        return *std::prev(end());
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if (!hasTracks())
            throw std::out_of_range("Track list is empty");

        m_tracklist.erase(std::prev(end()));
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
