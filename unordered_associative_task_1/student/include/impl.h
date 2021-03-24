#pragma once
#include <string>
#include <vector>
#include <unordered_set>

struct Song
{
public:
    Song(const std::string& name)
             : track_name {name}
    {
    }

    const std::string& name() const
    {
        return track_name;
    }

    bool operator<(const Song&) = delete;

    bool operator==(const Song& otherSong) const
    {
        return track_name == otherSong.track_name;
    }

private:
    std::string track_name;
};

using playlist = std::vector<Song>;

/**
 * @todo Implement function that will check if one playlist has the same songs
 * as the second one
 *
 * @example is_same_content({"a", "b", "c", "d"}, {"a", "c", "d", "b"}) -> true
 * @example is_same_content({"a", "b", "c", "d"}, {"a", "b", "e", "c"}) -> false
 *
 * @return true if first playlist is anagram of second
 */
bool is_same_content(const playlist& first_playlist, const playlist& second_playlist)
{
    auto songHash = [](const Song& song)
    {
        return std::hash<std::string>{}(song.name());
    };

    return std::unordered_multiset<Song, decltype(songHash)>{first_playlist.cbegin(), first_playlist.cend(), first_playlist.size(), songHash } ==
           std::unordered_multiset<Song, decltype(songHash)>{second_playlist.cbegin(), second_playlist.cend(), second_playlist.size(), songHash };
}
