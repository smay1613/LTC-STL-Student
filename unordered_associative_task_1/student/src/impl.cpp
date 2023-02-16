#include "impl.h"
#include <unordered_set>


namespace std {
	template <>
	struct hash<Song> {
		std::size_t operator()(const Song& s) const {
			return std::hash<std::string>()(s.name());
		}
	};
}

bool operator==(const Song& s1, const Song& s2) {
	return s1.name() == s2.name();
}

bool is_same_content(const playlist& first_playlist, const playlist& second_playlist) {
	std::unordered_multiset<Song> playlist1(first_playlist.begin(), first_playlist.end());
	std::unordered_multiset<Song> playlist2(second_playlist.begin(), second_playlist.end());
	return playlist1 == playlist2;
}