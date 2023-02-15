#include "impl.h"
#include <unordered_set>

struct SongHash {
	std::size_t operator ()(const Song& s) const {
		return std::hash<std::string>{}(s.name());
	}
};

struct SongEqual {
	bool operator()(const Song& s1, const Song& s2) const {
		return s1.name() == s2.name();
	}
};

template<typename T>
const bool isEqualSize(const T& p1, const T& p2) {
	return p1.size() == p2.size();
}

const bool operator== (const std::unordered_set<Song, SongHash, SongEqual>& p1, const std::unordered_set<Song, SongHash, SongEqual>& p2) {
	if (!isEqualSize(p1, p2)) {
		return false;
	}
	for (auto &song : p2) {
		if (p1.count(song) != 1){
			return false;
		}
	}
	return true;
}


bool is_same_content(const playlist& first_playlist, const playlist& second_playlist) {
	if (!isEqualSize(first_playlist, second_playlist)){
		return false;
	}
	std::unordered_set<Song, SongHash, SongEqual> playlist1(first_playlist.begin(), first_playlist.end());
	std::unordered_set<Song, SongHash, SongEqual> playlist2(second_playlist.begin(), second_playlist.end());
	return playlist1 == playlist2;
}