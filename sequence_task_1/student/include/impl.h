#pragma once
#include <string>
#include <iostream>

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

template<class Container>
class StaticPlaylist
{
public:
    /** @todo Member traits */
   using value_type = typename Container::value_type;
   using allocator_type = typename Container::allocator_type;
   using size_type = typename Container::size_type;
   using difference_type = typename Container::difference_type;
   using const_reference = typename Container::const_reference;
   using pointer = typename Container::pointer;
   using const_pointer = typename Container::const_pointer;
   using iterator = typename Container::iterator;
   using const_iterator = typename Container::const_iterator;
   using reverse_iterator = typename Container::reverse_iterator;
   using const_reverse_iterator = typename Container::const_reverse_iterator;
   using reference = typename Container::reference;

    /** @todo Iterators */

   const_iterator begin()
   {
      return m_tracklist.begin();
   }

   const_iterator end()
   {
      return m_tracklist.end();
   }

   reverse_iterator rbegin()
   {
      return m_tracklist.rbegin();
   }

   reverse_iterator rend()
   {
      return m_tracklist.rend();
   }

    /** @todo Constructor from any reversible sequence container */
   template<class T>
   StaticPlaylist(const T& other)
      : m_tracklist()
   {
      m_tracklist.assign(other.begin(), other.end());
   }

    /** @todo Assignment from any reversible sequence container */
   template<class T>
   StaticPlaylist& operator = (const T& other)
   {
      m_tracklist.clear();
      m_tracklist.assign(other.begin(), other.end());
      m_tracklist.shrink_to_fit();
      return *this;
   }

    /** @todo Add track from initializer */
    template<class... Args>
    const Song& play(Args&&... songData)
    {
       m_tracklist.emplace_back(std::forward<Args>(songData)...);
       return m_tracklist.back();
    }

    /** @todo Add track */
    const Song& play(const Song& song)
    {
       m_tracklist.push_back(song);
       return m_tracklist.back();
    }

    /** @todo Get first track in playlist stack */
    const Song& current() const
    {
       if (hasTracks())
       {
          return m_tracklist.front();
       }
       else
       {
          std::cout<< "No tracks to play!" << std::endl;
       }
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext()
    {
       bool hasNext = false;
       if (hasTracks())
       {
         m_tracklist.erase(begin());
         hasNext = 0 < count();
       }
       else
       {
          throw std::out_of_range("Tracklist has no tracks!");
       }
       std::string text = hasNext ? current().name : "No tracks to play!";
       std::cout<< text << std::endl;
    }

    /** @todo Amount of tracks in playlist */
    size_type count() const
    {
       m_tracklist.size();
    }

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const
    {
       return !m_tracklist.empty();
    }

private:
    Container m_tracklist;
};
