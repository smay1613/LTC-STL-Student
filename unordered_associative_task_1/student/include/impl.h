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
bool is_same_content(const playlist& first_playlist, const playlist& second_playlist){
    
    if(first_playlist.size() != second_playlist.size()){
        return false;
    }
    
    std::unordered_multiset<std::string> playlist1 {}, playlist2 {};

    for( const auto& s : first_playlist){
        playlist1.insert(s.name());
    }

    for( const auto& s : second_playlist){
        playlist2.insert(s.name());
    }
    
    return playlist1 == playlist2;
}
