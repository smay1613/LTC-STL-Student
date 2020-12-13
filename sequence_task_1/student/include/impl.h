#pragma once
#include <string>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

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
    using value_type      = typename Container::value_type;
    using reference       = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator        = typename Container::iterator;
    using const_iterator  = typename Container::const_iterator;
    using difference_type = typename Container::difference_type;
    using size_type       = typename Container::size_type;

    /** @todo Iterators */

    const_iterator begin () const
    {
        return m_tracklist.begin();
    }
    const_iterator end () const
    {
        return m_tracklist.end();
    }
    const_iterator cbegin()
    {
        return m_tracklist.cbegin();
    }
    const_iterator cend()
    {
        return m_tracklist.cend();
    }

    /** @todo Constructor from any reversible sequence container */

    template <typename T>
    StaticPlaylist(const T& container)
    {
        m_tracklist.assign(container.begin(), container.end());
    }

    /** @todo Assignment from any reversible sequence container */
    template <typename T>
    StaticPlaylist& operator=(T &container)
    {
        //assigns new songs to the container from the begging;
        m_tracklist.assign(container.begin(), container.end());
        return *this;
    }

    //StaticPlaylist& operator=(const StaticPlaylist &container);

    /** @todo Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData)
    {
        play(songData...);
    }

    /** @todo Add track */
    const Song& play(const Song& song)
    {
        m_tracklist.push_back(song);
        return m_tracklist.back();
    }

    /** @todo Get first track in playlist stack */
    const Song& current() const
    {
        return m_tracklist.front();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if(!m_tracklist.empty())
        {
            m_tracklist.erase(m_tracklist.begin());
        }
        else
        {
            throw std::out_of_range ("List is Empty");
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
