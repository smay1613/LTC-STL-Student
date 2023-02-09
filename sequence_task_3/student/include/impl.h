#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class DynamicPlaylist
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

	const_iterator begin() const {return m_tracklist.cbegin();}
	const_iterator end() const {return m_tracklist.cend();}

    DynamicPlaylist() = default;

    /** @todo Constructor from two iterators*/
	template <typename it>
	DynamicPlaylist(it first, it last) {
		m_tracklist.assign(first, last);
	}

    /** @todo Set track as currently played from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData) {
		return *m_tracklist.emplace(begin(), std::forward<Args>(songData)...);
	}

    /** @todo Set track as currently played from lvalue */
    const Song_t& play(const Song_t& song) { return *m_tracklist.insert(begin(), song);}

    /** @todo Set track to be played next from initializer */
    template<class... Args>
    void playNext(Args&&... songData) {
		short pos = hasTracks() ? 1:0;
		m_tracklist.emplace(begin() + pos, std::forward<Args>(songData)...);
	}

    /** @todo Set track to be played next from lvalue */
    void playNext(const Song_t& song)   { 
		short pos = hasTracks() ? 1:0;
		m_tracklist.insert(begin() + pos,1, song);
	}

    /** @todo Add track to the end of the queue from initializer */
    template<class... Args>
    void add(Args&&... songData) {
		m_tracklist.emplace_back(std::forward<Args>(songData)...);
	}

    /** @todo Add track to the end of the queue from lvalue */
    void add(const Song_t& song) {
		m_tracklist.push_back(song);
	}

    /** @todo Get first track in playlist queue */
    const Song_t& current() const {
		return m_tracklist.front();
	}

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext() {
		if (m_tracklist.empty()) {
			throw std::out_of_range("Out of range");
		}
		m_tracklist.pop_front();
	}

    /** @todo Amount of tracks in playlist */
    size_type count() const {return m_tracklist.size();}

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const {return !m_tracklist.empty();}

private:
    Container m_tracklist;
};
