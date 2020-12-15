#pragma once
#include <string>
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
    using value_type        = typename Container::value_type;
    using reference         = typename Container::reference;
    using const_reference   = typename Container::const_reference;
    using iterator          = typename Container::iterator;
    using const_iterator    = typename Container::const_iterator;
    using difference_type   = typename Container::difference_type;
    using size_type         = typename Container::size_type;

    /** @todo Iterators */
    const_iterator begin() const
    {
        return m_tracklist.begin();
    }

    const_iterator end() const
    {
        return m_tracklist.end();
    }

    /** @todo Constructor from any reversible sequence container */
    template<class T>
    StaticPlaylist(const T& other) : m_tracklist()
    {
        m_tracklist.assign(other.begin(), other.end());
    }

    /** @todo Assignment from any reversible sequence container */
    template<class T>
    StaticPlaylist& operator=(const T& other)
    {
        m_tracklist.assign(other.begin(), other.end());
        return *this;
    }

    /** @todo Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData)
    {
        m_tracklist.emplace(m_tracklist.begin(), std::forward<Args>(songData)... );

        return *m_tracklist.begin();
    }

    /** @todo Add track */
    const Song& play(const Song& song)
    {
        m_tracklist.emplace(m_tracklist.begin(), song);

        return *m_tracklist.begin();
    }

    /** @todo Get first track in playlist stack */
    const Song& current() const
    {
        return m_tracklist.front();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if(true == hasTracks())
        {
            m_tracklist.erase(std::remove(m_tracklist.begin(), m_tracklist.end(), current()), m_tracklist.end());
        }
        else
        {
            throw std::out_of_range("");
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