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
    using const_reverse_iterator = typename Container::const_reverse_iterator;

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

    const_reverse_iterator rbegin()
    {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator rend()
    {
        return const_reverse_iterator(begin());
    }

    /** @todo Constructor from any reversible sequence container */
    template <typename OtherContainer>
    StaticPlaylist(OtherContainer&& c)
        : m_tracklist(std::make_move_iterator(c.rbegin()), std::make_move_iterator(c.rend()))
    {
        std::cout << "StaticPlaylist(OtherContainer&& c)" << std::endl;
    }

    template <typename OtherContainer>
    StaticPlaylist(OtherContainer const& c)
        : m_tracklist(c.rbegin(), c.rend())
    {
        std::cout << "StaticPlaylist(OtherContainer const& c)" << std::endl;
    }

    /** @todo Assignment from any reversible sequence container */
    template <typename OtherContainer>
    StaticPlaylist& operator=(const OtherContainer& c)
    {
        std::cout << "StaticPlaylist& operator=(const OtherContainer& c))" << std::endl;
        m_tracklist.assign(c.rbegin(), c.rend());
        return *this;
    }

    template <typename OtherContainer>
    StaticPlaylist& operator=(OtherContainer&& c)
    {
        std::cout << "StaticPlaylist& operator=(OtherContainer&& c)" << std::endl;
        Container tmp_container(std::make_move_iterator(c.rbegin()), std::make_move_iterator(c.rend()));
        m_tracklist.swap(tmp_container);
        return *this;
    }

    /** @todo Add track from initializer */
    template <typename... Args>
    const Song& play(Args&&... songData)
    {
        std::cout << "const Song& play(Args&&... songData)" << std::endl;
        m_tracklist.emplace_back(Song { songData }...);
        return *rbegin();
    }

    /** @todo Add track */
    const Song& play(Song const& song)
    {
        std::cout << "const Song& play(Song const& song)" << std::endl;
        m_tracklist.push_back(song);
        return *rbegin();
    }

    /** @todo Get first track in playlist stack */
    const Song& current() const
    {
        if (!hasTracks()) {
            throw std::out_of_range("");
        }
        return *std::prev(end());
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if (!hasTracks()) {
            throw std::out_of_range("");
        }
        m_tracklist.erase(end());
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
