#pragma once
#include <string>
#include <vector>
#include <unordered_set>
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

/**
 * @todo Implement function that will check if one playlist has the same songs
 * as the second one
 *
 * @example is_same_content({"a", "b", "c", "d"}, {"a", "c", "d", "b"}) -> true
 * @example is_same_content({"a", "b", "c", "d"}, {"a", "b", "e", "c"}) -> false
 *
 * @return true if first playlist is anagram of second
 */

bool operator==(const Song& lhs, const Song& rhs) {
    return lhs.name() == rhs.name();
}

template<> struct std::hash<Song> {
    std::size_t operator()(Song const& s) const noexcept {
        return std::hash<string>{}(s.name());
    }
};

bool is_same_content(const playlist& first_playlist, const playlist& second_playlist){
    
    if(first_playlist.size() != second_playlist.size()){
        return false;
    }
    
    std::unordered_set<Song> unique_playlist(first_playlist.begin(), first_playlist.end());

    for( const auto& song : unique_playlist){

        const size_t counter1 = std::count(first_playlist.begin(), first_playlist.end(), song);
        const size_t counter2 = std::count(second_playlist.begin(), second_playlist.end(), song);

        if(counter1 != counter2){
            return false;
        }
    }
    return true;
}
