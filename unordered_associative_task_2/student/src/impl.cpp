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

/** @todo With help of std filesystem, lists all regular files under specified directory recursively*/
std::vector<std::string> listFiles(const std::string& directory)
{
    std::vector<std::string> fileList;

    for (auto& it : fs::recursive_directory_iterator(directory))
    {
        if (it.path().has_extension())
        {
            fileList.push_back(it.path().string());
        }
    }

    return fileList;
}

/** @todo Implement function that will remove group in if it has only one or zero elements */
void removeUniqueGroups(filtering_map& filteredData)
{
    for (auto it = filteredData.begin(); it != filteredData.end();)
    {
        if (it->second.size() <= 1)
        {
            it = filteredData.erase(it);
        }
        else
        {
            it++;
        }
    }
}

/** @todo Implement function that will transform map to a vector */
std::vector<std::vector<std::string>> flattenGrouped (const filtering_map& grouped)
{
    std::vector<std::vector<std::string>> flatGroups;

    std::vector<std::string> group;

    for (auto& it : grouped)
    {
        group.assign(it.second.begin(), it.second.end());
        flatGroups.push_back(group);
    }

    return flatGroups;
}

/** @todo Implement filtering files by different buckets by specified criteria*/
template<class FilterCriteria>
filtering_map filter(const std::vector<std::string>& files, FilterCriteria filter)
{
    filtering_map map;

    for (auto& file : files)
    {
        auto key = filter(file);

        map[key].push_back(file);
    }

    return map;
}

/** @note HELPER */
template<class Filter>
filtering_map groupDuplicates (const std::vector<std::string>& dataSource, Filter filterCriteria)
{
    auto grouped = filter(dataSource, filterCriteria);
    removeUniqueGroups(grouped);
    return grouped;
}

/**
 * @todo Implement function that fill find duplicated files under the directory recursively
 * @param rootPath - directory to check
 * @return list of duplicated files, grouped by content
 */
std::vector<std::vector<std::string> > findDuplicates(const std::string &rootPath)
{
    auto fileList = listFiles(rootPath);

    auto grouped = groupDuplicates(fileList,
        [](const std::string& file)
        {
            return xx_hash(file);
        }
    );

    return { flattenGrouped(grouped) };
}
