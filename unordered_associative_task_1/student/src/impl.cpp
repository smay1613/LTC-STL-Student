#include <unordered_map>

#include "impl.h"

bool is_anagram(const std::string& first, const std::string& second)
{
    std::unordered_map<char, int> map_converter;
    if (first.length() != second.length())
    {
        return false;
    }

    for (const char& c : first)
    {
        map_converter[c]++;
    }

    for (const char& c : second)
    {
        if (map_converter.end() == map_converter.find(c))
        {
            return false;
        }
        if (0 == (--map_converter[c]))
        {
            map_converter.erase(c);
        }
    }
    return map_converter.size() == 0;
}
