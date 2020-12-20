#include "impl.h"
#include <experimental/filesystem>
#include <experimental/unordered_map>
#include <fstream>
#include <numeric>
#include "xxhash.h"
#include <iostream>
#include <algorithm>

namespace fs = std::experimental::filesystem;

// use this for hashing
auto xx_hash = [] (const std::string &file)
{
    std::ifstream stream {file};

    if (!stream)
    {
        std::cerr << "File " << file << " can't be opened" << std::endl;
        return xxh::hash_t<64> {};
    }

    const auto length = fs::file_size(file);
    std::vector<char> buffer(length);
    stream.read(buffer.data(), static_cast<std::streamsize>(length)); //avoid varning: implicit conversion changes signedness: 'const unsigned long long' to 'std::streamsize' (aka 'long long')

    return xxh::xxhash<64>(buffer);
};

auto xx_file_size = [] (const std::string &file)
{
    return fs::file_size(file);
};

/** @todo Implement filtering files by different buckets by specified criteria*/
template<class FilterCriteria>
filtering_map filter(const std::vector<std::string>& files, FilterCriteria filter)
{
    filtering_map ret;
    for(auto fileName : files)
    {
        const size_t key = filter(fileName);
        if (ret.find(key) != ret.end())
        {
            ret[key].push_back(fileName);
        }
        else
        {
            ret.insert({filter(fileName), std::vector<std::string>{fileName}});
        }
    }

    return ret;
}

/** @note HELPER */
template<class Filter>
filtering_map groupDuplicates (const std::vector<std::string>& dataSource, Filter filterCriteria)
{
    auto grouped = filter(dataSource, filterCriteria);
    removeUniqueGroups(grouped);
    return grouped;
}

// With help of std filesystem, lists all regular files under specified directory recursively/
std::vector<std::string> listFiles(const std::string& directory)
{
    std::vector<std::string> ret;
    for(auto& p: fs::recursive_directory_iterator(directory))
    {
        if(fs::is_regular_file(p))
        {
            ret.push_back(p.path().string());
        }
    }
    return ret;
}

// Implement function that will remove group in if it has only one or zero elements
void removeUniqueGroups(filtering_map& filteredData)
{
    std::experimental::erase_if(filteredData, [](const auto& item) {
            return item.second.empty() || (item.second.size() == 1);
        });
}

// @todo Implement function that will transform map to a vector /
std::vector<std::string> flattenGrouped (const filtering_map& grouped)
{
    std::vector<std::string> ret;
    for(auto pair : grouped)
    {
        std::copy(pair.second.begin(), pair.second.end(), std::back_inserter(ret));
    }

    return ret;
}

/*
 * @todo Implement function that fill find duplicated files under the directory recursively
 * @param rootPath - directory to check
 * @return list of duplicated files, grouped by content
 */
std::vector<std::vector<std::string> > findDuplicates(const std::string &rootPath)
{
    const std::vector<std::string>& fileNames = listFiles(rootPath);

    // filter by content
    const filtering_map& contentGroup = groupDuplicates(fileNames, xx_hash);

    std::vector<std::vector<std::string> > ret;
    for(auto pair : contentGroup)
    {
        std::vector<std::string> group;
        std::copy(pair.second.begin(), pair.second.end(), std::back_inserter(group));
        if(!group.empty())
        {
            ret.emplace_back(group);
        }
    }




    // filter by size
    //const filtering_map sizeGroup = groupDuplicates(fileNames, xx_file_size);
    //const std::vector<std::string> flatSizeGroup = flattenGrouped(sizeGroup);
    //if(!flatSizeGroup.empty())
    //{
    //    ret.emplace_back(flatSizeGroup);
    //}

    return ret;
}
