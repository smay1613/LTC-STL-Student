#pragma once
#include <string>
#include <vector>
#include <algorithm>

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

bool is_in_playlist(const Song& search, const playlist& playlist)
{
    size_t count = std::count_if(playlist.begin(), playlist.end(), 
        [&](const Song& song) {
            return song.name() == search.name();
        }
    );

    return count > 0;
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
    if (first_playlist.size() != second_playlist.size())
        return false;
    
    for (auto& it : first_playlist)
    {
        if (!is_in_playlist(it, second_playlist))
            return false;
    }

    for (auto& it : second_playlist)
    {
        if (!is_in_playlist(it, first_playlist))
            return false;
    }

    return true;
}
