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
    /*
     // simple ...
    typedef Song         value_type;
    typedef Song&        reference;
    typedef const Song&  const_reference;
    typedef size_t	     size_type;
    typedef ptrdiff_t    difference_type;
    */
    typedef typename Container::value_type       value_type;
    typedef typename Container::reference        reference;
    typedef typename Container::const_reference  const_reference;
    typedef typename Container::size_type        size_type;
    typedef typename Container::difference_type  difference_type;
    //i don't know any other way to iterators
    typedef typename Container::iterator        iterator;
    typedef typename Container::const_iterator  const_iterator;

    /** Iterators */
    const_iterator begin() const
    {
        return m_tracklist.begin();
    }

    const_iterator end() const
    {
        return m_tracklist.end();
    }

    StaticPlaylist()
    : m_tracklist()
    {

    }

    /** Constructor from any reversible sequence container */
    //any container? Cheking needed AnyContainer is supported in compile time, like static_assert. Out of scope.
    template<class AnyContainer>
    StaticPlaylist(const AnyContainer& ac)
    : m_tracklist(ac.begin(), ac.end())
    {

    }

    StaticPlaylist( const StaticPlaylist& other )
    : m_tracklist(other.m_tracklist.begin(), other.m_tracklist.end())
    {

    }

    /** Assignment from any reversible sequence container */
    //any container? Cheking needed AnyContainer is supported in compile time, like static_assert. Out of scope.
    template<class AnyContainer>
    StaticPlaylist& operator=(const AnyContainer& ac)
    {
        m_tracklist.clear();
        m_tracklist.insert(m_tracklist.begin(), ac.begin(), ac.end());
        return *this;
    }

    StaticPlaylist& operator=( const StaticPlaylist& other )
    {
        if (this != &other && m_tracklist != other.m_tracklist)
        {
            m_tracklist = other.m_tracklist;
        }
        return *this;
    }

    /** Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData)
    {
        m_tracklist.emplace_back(songData...);
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
        return m_tracklist.front();
    }

    /** Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if(hasTracks())
        {
            //first is current, so erase first, second will be current
            m_tracklist.erase(m_tracklist.begin());
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
