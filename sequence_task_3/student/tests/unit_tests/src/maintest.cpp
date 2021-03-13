#include "maintest.h"
#include <vector>
#include <deque>
#include <list>

using namespace ::testing;

struct SongNoMove {
    SongNoMove() = delete;
    SongNoMove(const std::string& name, size_t year)
             : name {name},
               year {year}
    {
    }

    SongNoMove(SongNoMove&&) = delete;
    SongNoMove(const SongNoMove&) = delete;

    const std::string name;
    const size_t year;
};

struct Song
{
    std::string name;
    explicit Song(const std::string& song_name)
        : name {song_name}
    {
    }
};

bool operator==(const Song& lhs, const Song& rhs)
{
    return lhs.name == rhs.name;
}

using basic_container = std::deque<Song>;
using other_container = std::list<Song>;

using DefaultTracklist = DynamicPlaylist<basic_container, Song>;

TEST(Initialization, PlaylistInitBasic)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data.begin(), data.end()};
    EXPECT_TRUE(playlist.hasTracks());
}

TEST(Initialization, PlaylistInitOther2)
{
    other_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data.begin(), data.end()};
    EXPECT_TRUE(playlist.hasTracks());
}

TEST(TracklistCommon, Order)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data.begin(), data.end()};

    std::equal(playlist.begin(), playlist.end(), data.begin());
}

TEST(TracklistOperations, FromArguments)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data.begin(), data.end()};

    EXPECT_EQ(playlist.play("example3").name, "example3");
}

TEST(TracklistOperations, FromLvalue)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data.begin(), data.end()};

    Song newSong {"example3"};

    EXPECT_EQ(playlist.play(newSong), newSong);
}

TEST(TracklistOperations, NoUBToday)
{
    basic_container data {};
    DefaultTracklist playlist {data.begin(), data.end()};
    EXPECT_THROW(playlist.switchNext(), std::out_of_range);
}

TEST(TracklistOperations, Switch)
{
    basic_container data {Song {"example1"},
                          Song {"example2"},
                          Song {"example3"}};
    DefaultTracklist playlist {data.begin(), data.end()};
    EXPECT_EQ(playlist.current(), Song {"example1"});
    playlist.switchNext();
    EXPECT_EQ(playlist.current(), Song {"example2"});
    EXPECT_EQ(playlist.count(), 2);
}

TEST(TracklistOperations, FromSeveralArguments)
{
    DynamicPlaylist<std::list<SongNoMove>, SongNoMove> playlist {};

    EXPECT_EQ(playlist.play(std::string {"example3"}, 3000u).name,
              "example3");
}

TEST(TracklistOperations, PlayNextEmpty)
{
    DefaultTracklist playlist {};
    playlist.playNext(Song {"example1"});
    EXPECT_EQ(playlist.current().name,
              "example1");
}

TEST(TracklistOperations, PlayNextNonEmpty)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data.begin(), data.end()};

    Song newSong {"example3"};

    playlist.playNext(newSong);
    playlist.switchNext();
    EXPECT_EQ(playlist.current(), newSong);
}

TEST(TracklistOperations, PlayNextNonEmptyFromArgs)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data.begin(), data.end()};

    playlist.playNext("example3");
    playlist.switchNext();
    EXPECT_EQ(playlist.current().name, "example3");
}

TEST(TracklistOperations, AddFromArgs)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data.begin(), data.end()};

    playlist.add("example3");

    playlist.switchNext();
    playlist.switchNext();

    EXPECT_EQ(playlist.current().name, "example3");
}

TEST(TracklistOperations, AddFromLvalue)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data.begin(), data.end()};

    Song newSong {"example3"};
    playlist.add(newSong);

    playlist.switchNext();
    playlist.switchNext();

    EXPECT_EQ(playlist.current().name, "example3");
}
