#include "maintest.h"
#include <vector>
#include <deque>
#include <list>

using namespace ::testing;
struct Song
{
    std::string name;
    explicit Song(std::string song_name)
        : name {std::move(song_name)}
    {
    }
};

bool operator==(const Song& lhs, const Song& rhs)
{
    return lhs.name == rhs.name;
}

using basic_container = std::vector<Song>;
using other_container1 = std::deque<Song>;
using other_container2 = std::list<Song>;

using DefaultTracklist = StaticPlaylist<basic_container, Song>;

TEST(Traits, ContainerTraits)
{
    static_assert (std::is_same<DefaultTracklist::value_type,
                                Song>::value,
                   "Wrong value_type trait!");
    static_assert (std::is_same<DefaultTracklist::reference,
                                Song&>::value,
                   "Wrong reference trait!");
    static_assert (std::is_same<DefaultTracklist::const_reference,
                                const Song&>::value,
                   "Wrong const_reference trait!");
    static_assert (std::is_same<DefaultTracklist::iterator,
                                basic_container::iterator>::value,
                   "Wrong iterator trait!");
    static_assert (std::is_same<DefaultTracklist::const_iterator,
                                basic_container::const_iterator>::value,
                   "Wrong const_iterator trait!");
    static_assert (std::is_same<DefaultTracklist::difference_type,
                                ptrdiff_t>::value,
                   "Wrong difference_type trait!");
    static_assert (std::is_same<DefaultTracklist::size_type,
                                size_t>::value,
                   "Wrong size_type trait!");
}

TEST(Initialization, PlaylistInitBasic)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data};
    EXPECT_TRUE(playlist.hasTracks());
}

TEST(Initialization, PlaylistInitOther1)
{
    other_container1 data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data};
    EXPECT_TRUE(playlist.hasTracks());
}

TEST(Initialization, PlaylistInitOther2)
{
    other_container2 data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data};
    EXPECT_TRUE(playlist.hasTracks());
}

TEST(RangeFor, Iterators)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data};

    for (auto& entry : playlist)
    {
        static_assert (std::is_const<std::remove_reference<decltype (entry)>::type>::value,
                       "Iterator must be only const");
    }
}

TEST(TracklistCommon, Order)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data};

    std::reverse(data.begin(), data.end());
    EXPECT_TRUE(std::equal(playlist.begin(), playlist.end(), data.begin()));
}

TEST(TracklistOperations, AssignLvalue)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data};

    other_container1 newData {Song {"example0"}, Song {"example3"}};
    playlist = newData;

    EXPECT_EQ(playlist.count(), 2);
    EXPECT_EQ(playlist.current(), Song {"example0"});
}

TEST(TracklistOperations, FromArguments)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data};

    EXPECT_EQ(playlist.play("example3").name, "example3");
}

TEST(TracklistOperations, FromSeveralArguments)
{
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

    StaticPlaylist<std::list<SongNoMove>, SongNoMove> playlist {};

    EXPECT_EQ(playlist.play(std::string {"example3"}, 3000u).name, "example3");
}

TEST(TracklistOperations, FromLvalue)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    DefaultTracklist playlist {data};

    const Song newSong {"example3"};

    EXPECT_EQ(playlist.play(newSong), newSong);
}

TEST(TracklistOperations, NoUBToday)
{
    basic_container data {};
    DefaultTracklist playlist {data};
    EXPECT_THROW(playlist.switchNext(), std::out_of_range);
}

TEST(TracklistOperations, Switch)
{
    basic_container data {Song {"example1"},
                          Song {"example2"},
                          Song {"example3"}};
    DefaultTracklist playlist {data};
    EXPECT_EQ(playlist.current(), Song {"example1"});
    playlist.switchNext();
    EXPECT_EQ(playlist.current(), Song {"example2"});
    EXPECT_EQ(playlist.count(), 2);
}
