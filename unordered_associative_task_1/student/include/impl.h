#pragma once
#include <string>
#include <vector>
#include <bits/stdc++.h>
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

    bool operator==(const Song& s) const
    {
        return this->track_name == s.track_name;
    }

    friend struct SongHash;
private:
    std::string track_name;
};

struct SongHash
{
    std::size_t operator()(const Song& s) const 
    {
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
bool is_same_content(const playlist& first_playlist, const playlist& second_playlist)
{
    if(first_playlist.size() != second_playlist.size())
        return false;

    std::unordered_multiset<Song, SongHash> temp_playlist (first_playlist.begin(), first_playlist.end());

    bool found;
    for(auto const &track : second_playlist)
    {
        found = false;

        for(auto it = temp_playlist.begin(); it != temp_playlist.end(); ++it)
        {
            if (track.name() == it->name())
            {
                temp_playlist.erase(it);
                found = true;
                break;
            }
        }
        
        if(!found)
            return false;
    }

    if(temp_playlist.empty())
        return true;
    else
        return false;
};
