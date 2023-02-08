#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class StaticPlaylist
{
public:
    /** @todo Member traits */
    using value_type = typename Container::value_type;
    using allocator_type = typename Container::allocator_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using pointer = typename Container::pointer;
    using const_pointer = typename Container::const_pointer;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using size_type = typename Container::size_type;
    using difference_type = typename Container::difference_type;

    /** @todo Iterators */
    const_iterator begin() const {
        return m_tracklist.cbegin();
    }

    const_iterator end() const {
        return m_tracklist.cend();
    }

    const_iterator rbegin() const {
        return m_tracklist.rbegin();
    }

    const_iterator rend() const {
        return m_tracklist.rend();
    }

    const_iterator cbegin() const
    {
        return m_tracklist.cbegin();
    }

    const_iterator cend() const
    {
        return m_tracklist.cend();
    }

    const_iterator crbegin() const
    {
        return m_tracklist.crbegin();
    }

    const_iterator crend() const
    {
        return m_tracklist.crend();
    }

    StaticPlaylist() : m_tracklist() {}

    /** @todo Constructor from any reversible sequence container */
    template <class AnotherContainer>
    StaticPlaylist(const AnotherContainer& container) :
        m_tracklist(container.crbegin(), container.crend())
    {}

    /** @todo Assignment from any reversible sequence container */
    template <class AnotherContainer>
    StaticPlaylist<Container, Song_t>& operator=(const AnotherContainer& container)
    {
        m_tracklist.assign(container.rbegin(), container.rend());
        return *this;
    }

    /** @todo Add track from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData) {
        m_tracklist.emplace_back(std::forward<Args>(songData)...);
        return current();
    }

    /** @todo Add track */
    const Song_t& play(const Song_t& song) {
        m_tracklist.push_back(song);
        return current();
    }

    /** @todo Get first track in playlist stack */
    const Song_t& current() const {
        return m_tracklist.back();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext() {
        if (!hasTracks()) {
            throw std::out_of_range("Error switchNext: Track List is empty");
        }
        m_tracklist.pop_back();
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
