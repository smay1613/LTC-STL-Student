#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class StaticPlaylist
{
public:
    /** @todo Member traits */

    /** @todo Iterators */

    StaticPlaylist() = default;

    /** @todo Constructor from any reversible sequence container */

    /** @todo Assignment from any reversible sequence container */

    /** @todo Add track from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData);

    /** @todo Add track */
    const Song_t& play(const Song_t& song);

    /** @todo Get first track in playlist stack */
    const Song_t& current() const;

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext();

    /** @todo Amount of tracks in playlist */
    size_type count() const;

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const;

private:
    Container m_tracklist;
};
