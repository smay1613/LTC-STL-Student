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
    typedef typename Container::reference           reference;
    typedef typename Container::const_reference     const_reference;
    typedef typename Container::difference_type     difference_type;
    typedef typename Container::value_type          value_type;
    typedef typename Container::size_type           size_type;

    /** @todo Iterators */
    typedef typename Container::iterator            iterator;
    typedef typename Container::const_iterator      const_iterator;

    const_iterator begin() {
        return m_tracklist.begin();
    }

    const_iterator end() {
        return m_tracklist.end();
    }

    /** @todo Constructor from any reversible sequence container */
    template<class DataSource>
    StaticPlaylist(DataSource data) {
        m_tracklist.assign(data.begin(), data.end());
    }

    /** @todo Assignment from any reversible sequence container */
    template<class DataSource>
    StaticPlaylist operator=(const DataSource& source) {
        m_tracklist.clear();
        m_tracklist.assign(source.begin(), source.end());
        return *this;
    };


    /** @todo Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData) {
        m_tracklist.insert(m_tracklist.begin(), {Song(songData)...});
        return *m_tracklist.begin();
    };

    /** @todo Add track */
    const Song& play(const Song& song) {
        m_tracklist.insert(m_tracklist.begin(), song);
        return *m_tracklist.begin();
    }

    /** @todo Get first track in playlist stack */
    const Song& current() const {
        return *m_tracklist.begin();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext() {
        if(!m_tracklist.empty()) {
            m_tracklist.erase(m_tracklist.begin());
        } else {
            throw std::out_of_range("Out of range");
        }
    }

    /** @todo Amount of tracks in playlist */
    size_type count() const {
        return m_tracklist.size();
    }

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const {
        return !m_tracklist.empty();
    }

private:
    Container m_tracklist;
};
