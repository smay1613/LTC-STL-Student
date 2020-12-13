#pragma once
#include <string>
#include <utility>
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
    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using difference_type = typename Container::difference_type;
    using size_type = typename Container::size_type;

    /** @todo Iterators */
    const_iterator icurrent;

    /** @todo Constructor from any reversible sequence container */
    template <class Container2>
    StaticPlaylist(const Container2&);

    /** @todo Assignment from any reversible sequence container */
    template <class Container2>
    StaticPlaylist& operator= (const StaticPlaylist<Container2>&);

    /** @todo Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData);

    /** @todo Add track */
    const Song& play(const Song& song);

    /** @todo Get first track in playlist stack */
    const Song& current() const;

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext();

    /** @todo Amount of tracks in playlist */
    size_type count() const { return (size_type)std::distance(icurrent, end()); }

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const { return (icurrent != end()); }

    const_iterator begin() const { return m_tracklist.begin();  }
    const_iterator end() const { return m_tracklist.end();  }

private:
    Container m_tracklist;
};



template<class Container>
template <class Container2>
StaticPlaylist<Container>::StaticPlaylist(const Container2& track_list)
    :
      m_tracklist(track_list.begin(),track_list.end() )
{
    icurrent = m_tracklist.begin();
}

template<class Container>
template <class Container2>
StaticPlaylist<Container>& StaticPlaylist<Container>::operator= (const StaticPlaylist<Container2>& playList)
{
    if( &playList != this )
    {
        m_tracklist.assign(playList.begin(), playList.end());
        icurrent = m_tracklist.begin();
    }
    return *this;
}

template<class Container>
template< class... Args>
const Song& StaticPlaylist<Container>::play(Args&&... songData)
{
    icurrent = m_tracklist.insert(m_tracklist.end(), Song{std::forward<Args>(songData)...} );
    return current();
}

template<class Container>
const Song& StaticPlaylist<Container>::play(const Song& song)
{
    icurrent = m_tracklist.insert(m_tracklist.end(),song);
    return current();
}

template<class Container>
const Song& StaticPlaylist<Container>::current() const
{
    return (icurrent != m_tracklist.end() ) ? *icurrent : throw std::out_of_range("Song is not exist");
}

template<class Container>
void StaticPlaylist<Container>::switchNext()
{
    if ((icurrent+1) < m_tracklist.end())
    {
        icurrent = std::next(icurrent);
    }
    else
    {
         throw std::out_of_range("Next element does not exist");
    }
}
