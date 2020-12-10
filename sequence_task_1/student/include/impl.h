#pragma once
#include <string>

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
    const_iterator begin(){
        return m_tracklist.cbegin();
    }
    const_iterator end(){
        return m_tracklist.cend();
    }

    /** @todo Constructor from any reversible sequence container */
    template<class T>
    StaticPlaylist(const T& tracklist){
        m_tracklist.assign(tracklist.begin(), tracklist.end());
    }

    /** @todo Assignment from any reversible sequence container */
    template<class T>
    StaticPlaylist& operator=(const T& other){
        m_tracklist.clear();
        m_tracklist.assign(other.begin(), other.end());
        return *this;
    }

    /** @todo Add track from initializer */
    template<class T,class... Args>
    const Song& play(T& first, Args&&... songData){
        const Song& song = play(first);
        play(songData ...);
        return song;
    }
    template<class... Args>
    const Song& play(Args&&... songData){
          return play(songData ...);
    }

    /** @todo Add track */
    const Song& play(const Song& song){
        m_tracklist.push_back(song);
        return song;
    }
    const Song& play(Song& song){
        m_tracklist.push_back(song);
        return song;
    }
    const Song& play(const char* name){
        m_tracklist.push_back(Song(name));
        return m_tracklist.at(m_tracklist.size() - 1);
    }

    /** @todo Get first track in playlist stack */
    const Song& current() const{
        return m_tracklist.at(0);
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext(){
        m_tracklist.at(0);
        m_tracklist.erase(m_tracklist.begin());
    }

    /** @todo Amount of tracks in playlist */
    size_type count() const{
        return m_tracklist.size();
    }

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const {
        return  !m_tracklist.empty();
    }

private:
    Container m_tracklist;
};
