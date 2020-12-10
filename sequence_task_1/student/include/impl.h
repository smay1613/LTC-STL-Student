#pragma once
#include <stdexcept>
#include <string>

struct Song {
    std::string name;
    explicit Song(std::string song_name)
        : name { std::move(song_name) }
    {
    }
};

bool operator==(const Song& lhs, const Song& rhs)
{
    return lhs.name == rhs.name;
}

template <class Container>
class StaticPlaylist {
public:
    using ContainerTraits = std::iterator_traits<typename Container::iterator>;
    using value_type = typename ContainerTraits::value_type;
    using difference_type = typename ContainerTraits::difference_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using reverse_iterator = typename Container::reverse_iterator;
    using size_type = typename Container::size_type;

    /** @todo Member traits */

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
    template <typename OtherContainer>
    StaticPlaylist(OtherContainer c)
        : m_tracklist(c.begin(), c.end())
    {
    }

    /** @todo Assignment from any reversible sequence container */
    template <typename OtherContainer>
    StaticPlaylist& operator=(const OtherContainer& c)
    {
        Container tmp(c.begin(), c.end());
        std::swap(m_tracklist, tmp);
        return *this;
    }

    /** @todo Add track from initializer */
    template <typename... Args>
    const Song& play(Args&&... songData)
    {
        m_tracklist.insert(m_tracklist.begin(), std::forward<Song>(Song { std::string { songData } })...);
        return *m_tracklist.begin();
    }

    /** @todo Add track */
    const Song& play(Song const& song)
    {
        m_tracklist.insert(m_tracklist.begin(), song);
        return *m_tracklist.begin();
    }

    /** @todo Get first track in playlist stack */
    const Song& current() const
    {
        return *m_tracklist.begin();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if (!m_tracklist.empty()) {
            m_tracklist.erase(m_tracklist.begin());
        } else {
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
