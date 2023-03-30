#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class DynamicPlaylist
{
public:
    /** @todo Member traits */
    using const_pointer = typename Container::const_pointer;
    using const_reference = typename Container::const_reference;
    using const_iterator = typename Container::const_iterator;
    using iterator = typename Container::iterator;
    using reference = typename Container::reference;
    using pointer = typename Container::pointer;
    using ptrdiff_t = typename Container::difference_type;
    using size_type = typename Container::size_type;
    using value_type = typename Container::value_type;

    /** @todo Iterators */
    iterator begin()
    {
        return m_tracklist.begin();
    }

    iterator end()
    {
        return m_tracklist.end();
    }

    DynamicPlaylist() = default;

    /** @todo Constructor from two iterators*/
    template<class beginIt, class endIt>
    DynamicPlaylist(beginIt start, endIt end)
    {
        m_tracklist.assign(start, end);
    }

    /** @todo Set track as currently played from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData)
    {
        m_tracklist.emplace_front(std::forward<Args>(songData)...);
        return current();
    }

    /** @todo Set track as currently played from lvalue */
    const Song_t& play(const Song_t& song)
    {
        m_tracklist.push_front(song);
        return current();
    }

    /** @todo Set track to be played next from initializer */
    template<class... Args>
    void playNext(Args&&... songData)
    {
        auto pos = begin();

        if (pos != end())
            std::advance(pos, 1);

        m_tracklist.emplace(pos, std::forward<Args>(songData)...);
    }

    /** @todo Set track to be played next from lvalue */
    void playNext(const Song_t& song)
    {
        auto pos = begin();

        if (pos != end())
            std::advance(pos, 1);

        m_tracklist.insert(pos, song);
    }

    /** @todo Add track to the end of the queue from initializer */
    template<class... Args>
    void add(Args&&... songData)
    {
        m_tracklist.emplace_back(std::forward<Args>(songData)...);
    }

    /** @todo Add track to the end of the queue from lvalue */
    void add(const Song_t& song)
    {
        m_tracklist.push_back(song);
    }

    /** @todo Get first track in playlist queue */
    const Song_t& current() const
    {
        return m_tracklist.front();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        if (!hasTracks())
            throw std::out_of_range("No songs in playlist.\n");

        m_tracklist.pop_front();
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
