#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class StaticPlaylist
{
public:
    /** @todo Member traits */

    using value_type             = typename Container::value_type;
    using size_type              = typename Container::size_type;
    using difference_type        = typename Container::difference_type;
    using iterator               = typename Container::iterator;
    using const_iterator         = typename Container::const_iterator;
    using pointer                = typename Container::pointer;
    using const_pointer          = typename Container::const_pointer;
    using reference              = typename Container::reference;
    using const_reference        = typename Container::const_reference;
    using reverse_iterator       = typename Container::reverse_iterator;
    using const_reverse_iterator = typename Container::const_reverse_iterator;
    using allocator_type         = typename Container::allocator_type;

    /** @todo Iterators */

    const_iterator begin() const
    {
        return m_tracklist.cbegin();
    }
    const_iterator end() const
    {
        return m_tracklist.cend();
    }

    StaticPlaylist() = default;

    /** @todo Constructor from any reversible sequence container */

    template<class AnyContainer>
    StaticPlaylist(const AnyContainer& container)
        : m_tracklist{container.crbegin(), container.crend()}
    {}

    /** @todo Assignment from any reversible sequence container */

    template<class AnyContainer>
    StaticPlaylist& operator=(const AnyContainer& container)
    {
        m_tracklist.assign(container.crbegin(), container.crend());
        return *this;
    }

    /** @todo Add track from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData)
    {
        return *m_tracklist.emplace(m_tracklist.end(), std::forward<Args>(songData)...);
    }

    /** @todo Add track */
    const Song_t& play(const Song_t& song)
    {
        return *m_tracklist.insert(m_tracklist.end(), song);
    }

    /** @todo Get first track in playlist stack */
    const Song_t& current() const
    {
        return m_tracklist.back();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
        m_tracklist.erase(std::prev(m_tracklist.end()));
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
