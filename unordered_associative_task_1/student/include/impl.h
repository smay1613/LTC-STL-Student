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

    bool operator==(const Song& s){
        return track_name == s.track_name;
    }

    friend struct SongHash;
    
private:
    std::string track_name;
};

struct SongHash
{
    std::size_t operator()(const Song& s) const {
        return std::hash<std::string>()(s.track_name);
    }
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
bool is_same_content(const playlist& first_playlist, const playlist& second_playlist){

    if (first_playlist.size() != second_playlist.size()){
        return false;
    }

    std::unordered_set <Song, SongHash> first_playlist_set(first_playlist.begin(), first_playlist.end());
    std::unordered_set <Song, SongHash> second_playlist_set(second_playlist.begin(), second_playlist.end());

    for (const auto &s : first_playlist_set){
        if (second_playlist_set.find(s) == second_playlist_set.end()){
            return false;
        }
    }

    return true;

}
