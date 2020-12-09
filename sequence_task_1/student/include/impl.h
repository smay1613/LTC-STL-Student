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

    /** @todo Iterators */

    /** @todo Constructor from any reversible sequence container */

    /** @todo Assignment from any reversible sequence container */

    /** @todo Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData);

    /** @todo Add track */
    const Song& play(const Song& song);

    /** @todo Get first track in playlist stack */
    const Song& current() const;

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext();

    /** @todo Amount of tracks in playlist */
    size_type count() const;

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const;

private:
    Container m_tracklist;
};
