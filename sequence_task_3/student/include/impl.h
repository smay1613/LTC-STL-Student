#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class DynamicPlaylist
{
public:
    /** @todo Member traits */

    /** @todo Iterators */

    DynamicPlaylist() = default;

    /** @todo Constructor from two iterators*/

    /** @todo Set track as currently played from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData);

    /** @todo Set track as currently played from lvalue */
    const Song_t& play(const Song_t& song);

    /** @todo Set track to be played next from initializer */
    template<class... Args>
    void playNext(Args&&... songData);

    /** @todo Set track to be played next from lvalue */
    void playNext(const Song_t& song);

    /** @todo Add track to the end of the queue from initializer */
    template<class... Args>
    void add(Args&&... songData);

    /** @todo Add track to the end of the queue from lvalue */
    void add(const Song_t& song);

    /** @todo Get first track in playlist queue */
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
