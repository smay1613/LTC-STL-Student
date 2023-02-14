#pragma once
#include <unordered_set>
#include <string>
#include <vector>

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
    std::unordered_multiset<std::string> first_playlistset;
    std::unordered_multiset<std::string> second_playlistset;

    for( auto &song : first_playlist)
    {
        first_playlistset.emplace(song.name());
    }
    for( auto &song : second_playlist)
    {
        second_playlistset.emplace(song.name());
    }

    return first_playlistset == second_playlistset;
}
