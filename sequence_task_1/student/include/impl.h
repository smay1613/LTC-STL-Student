#pragma once
#include <string>
#include <iostream>

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
    typedef typename Container::size_type size_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;
    typedef typename Container::difference_type difference_type;
    //typedef typename Container::pointer pointer;

    /** @todo Iterators */
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;

    const_iterator begin() {return m_tracklist.begin();}
    const_iterator end() {return m_tracklist.end();}

    const_iterator cbegin() {return m_tracklist.cbegin();}
    const_iterator cend() {return m_tracklist.cend();}

    /** @todo Constructor from any reversible sequence container */
    template<class AnyContainer> StaticPlaylist(const AnyContainer& trackList) {
        m_tracklist.assign(trackList.begin(), trackList.end());
    }

    /** @todo Assignment from any reversible sequence container */
    template<class AnyContainer> StaticPlaylist& operator=(const AnyContainer& trackList){
        m_tracklist.assign(trackList.begin(), trackList.end());
        return *this;
    }

    /** @todo Amount of tracks in playlist */
    size_type count() const{
        return m_tracklist.size();
    }

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const{
        return count() > 0;
    }

    /** @todo Get first track in playlist stack */
    const Song& current() const{
        if (hasTracks()) {
            std::cout << m_tracklist.front().name << "\n";
            return m_tracklist.front();
        } else {
            throw std::out_of_range("Tried to get element that does not exist");
        }
    }

    /** @todo Add track */
    const Song& play(const Song& song){
        std::cout << "It does not enter this method in test FromLvalue\n";
        m_tracklist.insert(m_tracklist.begin(), song);
        std::cout << current().name << "\n";
        return current();
    }

    /** @todo Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData){
        std::cout << "Instead it gets here in both tests FromArguments and FromLvalue\n";
        m_tracklist.insert(m_tracklist.begin(), Song{songData...});
        return current();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext(){
        if(hasTracks()) {
            m_tracklist.erase(m_tracklist.begin());
        } else {
            throw std::out_of_range("Tried to skip past end");
        }
    }

private:
    Container m_tracklist;
};
