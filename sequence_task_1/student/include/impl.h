#pragma once
#include <string>
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
    using size_type       = typename Container::size_type;
    using allocator_type  = typename Container::allocator_type;
    using difference_type = typename Container::difference_type;
    using iterator        = typename Container::iterator;
    using const_iterator  = typename Container::const_iterator;
    using reference       = typename Container::reference;
    using const_reference = typename Container::const_reference;

    /** @todo Iterators */
    const_iterator begin()
    {
        return m_tracklist.cbegin();
    }

    const_iterator end()
    {
        return m_tracklist.cend();
    }

    /** @todo Constructor from any reversible sequence container */
    template<class OtherContainer>
    StaticPlaylist(const OtherContainer& otherConatiner)
        : m_tracklist(otherConatiner.cbegin(), otherConatiner.cend())
    {}

    /** @todo Assignment from any reversible sequence container */
    template<class OtherContainer>
    Container& operator=(const OtherContainer& otherConatiner)
    {
        m_tracklist.assign(otherConatiner.cbegin(), otherConatiner.cend());
        return m_tracklist;
    }

    /** @todo Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData)
    {
        return *m_tracklist.insert(end(), {Song(std::forward<Args>(songData))...});
    }

    /** @todo Add track */
    const Song& play(const Song& song)
    {
        return m_tracklist.push_back(song);
    }

    /** @todo Get first track in playlist stack */
    const Song& current() const
    {
        if (!hasTracks())
        {
            throw std::out_of_range("Playlist is empty");
        }
        return m_tracklist.front();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if (!hasTracks())
        {
            throw std::out_of_range("Playlist is empty");
        }
        m_tracklist.erase(begin());
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
