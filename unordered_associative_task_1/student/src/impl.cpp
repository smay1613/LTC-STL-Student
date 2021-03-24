#include "impl.h"
#include "unordered_set"

bool is_same_content(const playlist &first_playlist, const playlist &second_playlist) {
    auto songHasher = [](const Song& s){
        return std::hash<std::string>{}(s.name());
    };
    std::unordered_multiset<Song, decltype(songHasher)> first
        (first_playlist.begin(), first_playlist.end(), first_playlist.size(), songHasher);
    std::unordered_multiset<Song, decltype(songHasher)> second
            (second_playlist.begin(), second_playlist.end(), second_playlist.size(), songHasher);
    return first==second;
}