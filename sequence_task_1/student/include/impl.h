#ifndef _SEQUANCE_TASK_1_
#define _SEQUANCE_TASK_1_

#include <string>
#include <memory>
#include <utility>

struct Song
{
    std::string name;
    explicit Song(std::string song_name)
        : name{std::move(song_name)}
    {
    }
};

bool operator==(const Song &lhs, const Song &rhs)
{
    return lhs.name == rhs.name;
}

template <class Container>
class StaticPlaylist
{
public:
    /** @todo Member traits */

    typedef typename Container::size_type           size_type;
    typedef typename Container::value_type          value_type;
    typedef typename Container::reference           reference;
    typedef typename Container::const_reference     const_reference ;
    //typedef typename Container::type type;

    /** @todo Iterators */
    typedef typename Container::iterator            iterator;
    typedef typename Container::const_iterator      const_iterator;
    typedef typename iterator::difference_type      difference_type;
    typedef typename iterator::pointer              pointer;
    typedef const pointer                           const_pointer;

    const_iterator begin()
    {
        return m_tracklist.begin();
    }

    const_iterator end()
    {
        return std::end(m_tracklist);
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
   
    template <class TPlaylist>
    StaticPlaylist(const TPlaylist& other)
        :m_tracklist()
    {
        m_tracklist.assign(other.begin(), other.end());
    }

    /** @todo Assignment from any reversible sequence container */
    template <class TPlaylist>
    StaticPlaylist& operator=(TPlaylist other)
    {
        m_tracklist.clear();
        m_tracklist.assign(other.begin(), other.end());
        m_tracklist.shrink_to_fit();
        return *this;
    }

    /** @todo Add track from initializer */
    template <class... Args>
    const Song &play(Args &&... songData)
    {
        size_type current_size = count();
        m_tracklist.insert(m_tracklist.end(), {Song(songData)...});
        return m_tracklist.at(current_size);
    }

    /** @todo Add track */
    const Song &play(const Song &song)
    {
        m_tracklist.push_back(song);
        return song;
    }

    /** @todo Get first track in playlist stack */
    const Song &current() const
    {
        return m_tracklist.front();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        //TODO: Was implemented safety firt, but test was NOK
        // if(!m_tracklist.empty())
        // {
        //     m_tracklist.erase(m_tracklist.begin());
        // }

        m_tracklist.at(1);
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

#endif // _SEQUANCE_TASK_1_
