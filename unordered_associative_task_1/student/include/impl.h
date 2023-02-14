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

namespace std{

    template <> class hash <Song>{
        public:
        size_t operator()(const Song & song) const{
            return std::hash<std::string>{}(song.name());
        }
    };
}

 bool operator==(const Song & lhs, const Song & rhs) {
        return lhs.name()==rhs.name();
    }

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
    std::unordered_multiset<Song> first_set (first_playlist.begin(),first_playlist.end());
    std::unordered_multiset<Song> second_set (second_playlist.begin(),second_playlist.end());
    return (first_set==second_set);

}
