#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <iostream>

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

    bool operator==(const Song& t) const
    {
        return name() == t.name();
    }

private:
    std::string track_name;
};

struct MySongHash
{
    size_t operator()(const Song& song) const
    {
        return std::hash<std::string>{}(song.name());
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
bool is_same_content(const playlist& first_playlist, const playlist& second_playlist)
{
    std::unordered_set<Song, MySongHash> playlist1{first_playlist.begin(), first_playlist.end()};
    std::unordered_set<Song, MySongHash> playlist2{second_playlist.begin(), second_playlist.end()};
    
    if (first_playlist.size() != second_playlist.size())
        return false;

    if (playlist1.size() != playlist2.size())
        return false;

    for (auto& it : first_playlist)
    {
        if (playlist2.count(it) == 0)
            return false;
    }

    return true;
}
