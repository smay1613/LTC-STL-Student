#include "maintest.h"
#include <vector>
#include <deque>
#include <list>

using namespace ::testing;

using basic_container = std::vector<Song>;
using other_container1 = std::deque<Song>;
using other_container2 = std::list<Song>;

using Tracklist = StaticPlaylist<basic_container>;

TEST(Traits, ContainerTraits)
{
    static_assert (std::is_same<Tracklist::value_type,
                                Song>::value,
                   "Wrong value_type trait!");
    static_assert (std::is_same<Tracklist::reference,
                                Song&>::value,
                   "Wrong reference trait!");
    static_assert (std::is_same<Tracklist::const_reference,
                                const Song&>::value,
                   "Wrong const_reference trait!");
    static_assert (std::is_same<Tracklist::iterator,
                                basic_container::iterator>::value,
                   "Wrong iterator trait!");
    static_assert (std::is_same<Tracklist::const_iterator,
                                basic_container::const_iterator>::value,
                   "Wrong const_iterator trait!");
    static_assert (std::is_same<Tracklist::difference_type,
                                ptrdiff_t>::value,
                   "Wrong difference_type trait!");
    static_assert (std::is_same<Tracklist::size_type,
                                size_t>::value,
                   "Wrong size_type trait!");
}

TEST(Initialization, PlaylistInitBasic)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    Tracklist playlist {data};
    EXPECT_TRUE(playlist.hasTracks());
}

TEST(Initialization, PlaylistInitOther1)
{
    other_container1 data {Song{"example1"}, Song{"example2"}};
    Tracklist playlist {data};
    EXPECT_TRUE(playlist.hasTracks());
}

TEST(Initialization, PlaylistInitOther2)
{
    other_container2 data {Song{"example1"}, Song{"example2"}};
    Tracklist playlist {data};
    EXPECT_TRUE(playlist.hasTracks());
}

TEST(Initialization, RangeFor)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    Tracklist playlist {data};

    for (auto& entry : playlist)
    {
        static_assert (std::is_const<std::remove_reference<decltype (entry)>::type>::value,
                       "Iterator must be only const");
    }
}

TEST(Initialization, Order)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    Tracklist playlist {data};

    std::reverse(data.begin(), data.end());
    std::equal(playlist.begin(), playlist.end(), data.begin());
}

TEST(Initialization, AssignLvalue)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    Tracklist playlist {data};

    other_container1 newData {Song {"example0"}, Song {"example3"}};
    playlist = newData;

    EXPECT_EQ(playlist.count(), 2);
    EXPECT_EQ(playlist.current(), Song {"example0"});
}

TEST(Initialization, FromArguments)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    Tracklist playlist {data};

    EXPECT_EQ(playlist.play("example3").name, "example3");
}

TEST(Initialization, FromLvalue)
{
    basic_container data {Song{"example1"}, Song{"example2"}};
    Tracklist playlist {data};

    const Song newSong {"example3"};

    EXPECT_EQ(playlist.play(newSong), newSong);
}

TEST(Initialization, NoUBToday)
{
    basic_container data {};
    Tracklist playlist {data};
    EXPECT_THROW(playlist.switchNext(), std::out_of_range);
}

TEST(Initialization, Switch)
{
    basic_container data {Song {"example1"},
                          Song {"example2"},
                          Song {"example3"}};
    Tracklist playlist {data};
    EXPECT_EQ(playlist.current(), Song {"example1"});
    playlist.switchNext();
    EXPECT_EQ(playlist.current(), Song {"example2"});
    EXPECT_EQ(playlist.count(), 2);
}
