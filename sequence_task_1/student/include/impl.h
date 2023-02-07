#pragma once
#include <vector>
#include <string>
#include <stdexcept>



template<class Container, class Song_t>
class StaticPlaylist
{
public:
    /** @todo Member traits */
    typedef Song_t value_type;
    typedef Song_t& reference;
    typedef const Song_t & const_reference;
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    /** @todo Iterators */
      const_iterator begin() const{
        return m_tracklist.cbegin();
    };
    const_iterator end() const{
        return m_tracklist.cend();
    };

    StaticPlaylist() = default;

    /** @todo Constructor from any reversible sequence container */
 
    template<class OtherContainer> StaticPlaylist(const OtherContainer & tracklist){
       m_tracklist.assign(tracklist.rbegin(),tracklist.rend());
    }

    /** @todo Assignment from any reversible sequence container */
    template<class OtherContainer> StaticPlaylist & operator=(const OtherContainer & other){
        m_tracklist.assign(other.rbegin(),other.rend());
        return *this;
    }
    /** @todo Add track from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData){
        m_tracklist.emplace(end(),std::forward<Args>(songData)...);
        return current();
    }

    /** @todo Add track */
    const Song_t& play(const Song_t& song){
        m_tracklist.insert(end(),song);
        return current();
    }

    /** @todo Get first track in playlist stack */
    const Song_t& current() const{
       return m_tracklist.back();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext(){
        if(m_tracklist.empty()){
            throw std::out_of_range("Out of Range");
        }
        m_tracklist.pop_back();

    }

    /** @todo Amount of tracks in playlist */
    size_type count() const{
        return m_tracklist.size();
    }

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const{   
    return !(m_tracklist.empty());
    };



private:
    Container m_tracklist;
};

