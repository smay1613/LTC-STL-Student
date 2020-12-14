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
    /** Member traits */

    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using size_type = typename Container::size_type;
    using difference_type = typename Container::difference_type;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;

    /** Iterators */
    const_iterator begin() const
    {
        return m_tracklist.begin();
    }

    const_iterator end() const
    {
        return m_tracklist.end();
    }

    const_iterator cbegin()  const
    {
        return m_tracklist.cbegin();
    }

    const_iterator cend() const
    {
        return m_tracklist.cend();
    }

    StaticPlaylist()
    : m_tracklist()
    {

    }

    /** Constructor from any reversible sequence container */
    //any container? Cheking needed AnyContainer is supported in compile time, like static_assert. Out of scope.
    template<class AnyContainer>
    StaticPlaylist(const AnyContainer& ac)
    : m_tracklist(ac.rbegin(), ac.rend())
    {

    }

    StaticPlaylist( const StaticPlaylist& other )
    : m_tracklist(other.m_tracklist.rbegin(), other.m_tracklist.rend())
    {

    }

    /** Assignment from any reversible sequence container */
    //any container? Cheking needed AnyContainer is supported in compile time, like static_assert. Out of scope.
    template<class AnyContainer>
    StaticPlaylist& operator=(const AnyContainer& ac)
    {
        m_tracklist.assign(ac.rbegin(), ac.rend());
        return *this;
    }

    /** Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData)
    {
        m_tracklist.emplace_back(std::forward<Args>(songData)...);
        return m_tracklist.back();
    }

    /** Add track */
    const Song& play(const Song& song)
    {
        m_tracklist.push_back(song);
        return m_tracklist.back();
    }

    /** Get first track in playlist stack */
    const Song& current() const
    {
        return m_tracklist.back();
    }

    /** Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if(hasTracks())
        {
            (void)m_tracklist.pop_back();
        }
        else
        {
            throw std::out_of_range("switchNext - track list is empty");
        }
    }

    /** Amount of tracks in playlist */
    size_type count() const
    {
        return m_tracklist.size();
    }

    /** Checks if playlist has any playable tracks */
    bool hasTracks() const
    {
        return !m_tracklist.empty();
    }

private:
    Container m_tracklist;
};
