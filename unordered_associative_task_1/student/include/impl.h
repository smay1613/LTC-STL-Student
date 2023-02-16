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

    bool operator==(const Song& other)const
    {
        return track_name == other.name();
    }

private:
    std::string track_name;
};

using playlist = std::vector<Song>;

namespace std
{
    template<>
    struct hash<Song>
    {
        size_t operator()(const Song& key)const
        {
            return hash<std::string>()(key.name());
        }
    };
}
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
    std::unordered_multiset<Song> first_playlistset(first_playlist.begin(),first_playlist.end());
    std::unordered_multiset<Song> second_playlistset(second_playlist.begin(),second_playlist.end());

    return first_playlistset == second_playlistset;
}
