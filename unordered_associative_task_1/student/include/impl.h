#pragma once
#include <string>
#include <vector>
#include <unordered_map>
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
    std::unordered_map<std::string, int> songs;
    
    //POPULATING MAP
    for(auto& s : first_playlist){
        if(songs.find(s.name()) == songs.end()) songs.insert({s.name(), 1});
        else songs.find(s.name())->second++;
    } 

    //DELETING ELEMENTS FROM MAP
    for(auto& s : second_playlist){
        const auto& song =  songs.find(s.name());
        if(song != songs.end()){
            song->second--;
            if(song->second == 0) songs.erase(song->first);
        }
        else return false;
    }

    return songs.empty();
}