#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class DynamicPlaylist
{
public:
    /** Member traits */
    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using difference_type = typename Container::difference_type;
    using size_type = typename Container::size_type;
    using self_type = DynamicPlaylist<Container, Song_t>;

    /** Iterators */
    const_iterator begin() const {
        return m_tracklist.cbegin();
    }

    const_iterator end() const {
        return m_tracklist.cend();
    }

    DynamicPlaylist() = default;
    DynamicPlaylist(const self_type& other) = default;
    DynamicPlaylist(self_type&& other) = default;
    self_type& operator=(const self_type& rhs) = default;
    self_type& operator=(self_type&& rhs) = default;

    /** Constructor from two iterators*/
    template <class Iter>
    DynamicPlaylist(Iter iterBegin, Iter iterEnd)
         : m_tracklist(iterBegin, iterEnd)
     {}

    /** Set track as currently played from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData) {
        m_tracklist.emplace_front(std::forward<Args>(songData)...);
        return current();
    }

    /** Set track as currently played from lvalue */
    const Song_t& play(const Song_t& song) {
        m_tracklist.push_front(song);
        return current();
    }

    /** Set track to be played next from initializer */
    template<class... Args>
    void playNext(Args&&... songData) {
        if (!hasTracks()) {
            play(std::forward<Args>(songData)...);
            return;
        }
        m_tracklist.emplace(std::next(m_tracklist.begin()), std::forward<Args>(songData)...);
    }

    /** Set track to be played next from lvalue */
    void playNext(const Song_t& song) {
        if (!hasTracks()) {
            play(song);
            return;
        }
        m_tracklist.insert(std::next(m_tracklist.begin()), song);
    }

    /** Add track to the end of the queue from initializer */
    template<class... Args>
    void add(Args&&... songData) {
        m_tracklist.emplace_back(std::forward<Args>(songData)...);
    }

    /** Add track to the end of the queue from lvalue */
    void add(const Song_t& song) {
        m_tracklist.push_back(song);
    }

    /** Get first track in playlist queue */
    const Song_t& current() const {
        return m_tracklist.front();
    }

    /** Skip to the next track in playlist, remove current */
    void switchNext() {
        if (!hasTracks()) {
            throw  std::out_of_range("switchNext");
        }
        m_tracklist.pop_front();
    }

    /** Amount of tracks in playlist */
    size_type count() const {
        return m_tracklist.size();
    }

    /** Checks if playlist has any playable tracks */
    bool hasTracks() const {
        return count() > 0;
    }

private:
    Container m_tracklist;
};
