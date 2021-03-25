#include "impl.h"
#include <experimental/filesystem>
#include <fstream>
#include <numeric>
#include "xxhash.h"
#include <iostream>

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
    stream.read(buffer.data(), length);

    return xxh::xxhash<64>(buffer);
};

auto fileSize = [] (const std::string &file)
{
    return fs::file_size(fs::path(file));
};

/** @todo Implement filtering files by different buckets by specified criteria*/
template<class FilterCriteria>
filtering_map filter(const std::vector<std::string>& files, FilterCriteria filter)
{
    filtering_map groups;
    size_t groupKey;
    for(const auto& file : files)
    {
        groupKey = filter(file);
        groups[groupKey].push_back(file);
    }
    return groups;
}

/** @note HELPER */
template<class Filter>
filtering_map groupDuplicates (const std::vector<std::string>& dataSource, Filter filterCriteria)
{
    auto grouped = filter(dataSource, filterCriteria);
    removeUniqueGroups(grouped);
    return grouped;
}

std::vector<std::string> listFiles(const std::string& directory)
{
    std::vector<std::string> filePaths;
    for(const auto& dirEntry : fs::recursive_directory_iterator(directory))
    {
        if (fs::is_regular_file(dirEntry.path()))
            filePaths.push_back(dirEntry.path().string());
    }
    return filePaths;
}

void removeUniqueGroups(filtering_map& filteredData)
{
    std::vector<size_t> groupsToRemove;
    for (const auto& filteredGroup : filteredData)
    {
        if (filteredGroup.second.size() <= 1)
            groupsToRemove.push_back(filteredGroup.first);
    }

    for (const size_t key : groupsToRemove)
    {
        filteredData.erase(key);
    }
}

std::vector<std::string> flattenGrouped (const filtering_map& grouped)
{
    std::vector<std::string> accumulator;
    for (const auto& group : grouped)
    {
        accumulator.insert(accumulator.end(), group.second.begin(), group.second.end());
    }
    return accumulator;
}
std::vector<std::vector<std::string> > findDuplicates(const std::string &rootPath)
{
    // filter by size
    // filter by content
    // flatten

    std::vector<std::string> files = listFiles(rootPath);
    filtering_map sizeGroupedMap = groupDuplicates(files, fileSize);
    filtering_map hashGroupedMap = groupDuplicates(flattenGrouped(sizeGroupedMap), xx_hash);

    std::vector<std::vector<std::string> > groupsOfEqualFiles;
    for (const auto& mapElement : hashGroupedMap)
    {
        groupsOfEqualFiles.push_back(mapElement.second);
    }
    return groupsOfEqualFiles;
}
