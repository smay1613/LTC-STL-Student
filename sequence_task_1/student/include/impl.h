#pragma once
#include <iostream>
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
    /** @todo Member traits */
    using value_type = typename Container::value_type;
    using difference_type = typename Container::difference_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using reverse_iterator = typename Container::reverse_iterator;

    /** @todo Iterators */
    const_iterator begin() const
    {
        return m_tracklist.begin();
    }

    const_iterator end() const
    {
        return m_tracklist.end();
    }

    const_iterator cbegin() const
    {
        return m_tracklist.cbegin();
    }

    const_iterator cend() const
    {
        return m_tracklist.cend();
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
        m_tracklist.assign(c.begin(), c.end());
        return *this;
    }

    /** @todo Add track from initializer */
    template <typename... Args>
    const Song& play(Args&&... songData)
    {
        std::cout << "const Song& play(Args&&... songData)" << std::endl;
        m_tracklist.insert(m_tracklist.begin(), Song {  songData } ...);
        return *m_tracklist.begin();
    }

    /** @todo Add track */
    const Song& play(Song const& song)
    {
        std::cout << "const Song& play(Song const& song)" << std::endl;
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
