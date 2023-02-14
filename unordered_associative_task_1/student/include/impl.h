#pragma once
#include <set>
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
    std::multiset<std::string> first_playlistset;
    std::multiset<std::string> second_playlistset;
    for( auto &song : first_playlist)
    {
        first_playlistset.emplace(song.name());
    }
    for( auto &song : second_playlist)
    {
        second_playlistset.emplace(song.name());
    }

    auto match_count = [&](std::string songname)
    {
        return first_playlistset.erase(songname) == second_playlistset.erase(songname);
    };

    for(const auto &song : second_playlist)
    {
        if(!match_count(song.name()))
        {
            return false;
        }
    }

    return first_playlistset.empty();
}
