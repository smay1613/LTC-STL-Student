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


/** @todo Implement filtering files by different buckets by specified criteria*/
template<class FilterCriteria>
filtering_map filter(const std::vector<std::string>& files, FilterCriteria filter)
{
    filtering_map filteredFiles;
    for (auto const& f : files) {
        filteredFiles[filter(f)].push_back(f);
    }
    return filteredFiles;
}


/** @note HELPER */
template<class Filter>
filtering_map groupDuplicates (const std::vector<std::string>& dataSource, Filter filterCriteria)
{
    auto grouped = filter(dataSource, filterCriteria);
    removeUniqueGroups(grouped);
    return grouped;
}

std::vector<std::vector<std::string> > findDuplicates(const std::string &rootPath)
{
    // filter by size
    filtering_map filesBySize = groupDuplicates(listFiles(rootPath),
        [](const std::string& file) { return fs::file_size(file); });

    std::vector<std::string> filesList = flattenGrouped(filesBySize);

    // filter by content
    filtering_map filesByContent = groupDuplicates(filesList,
        [](const std::string& file) { return xx_hash(file); });

    // flatten
    std::vector<std::vector<std::string>> result;
    for (auto const& file : filesByContent) {
        if (result.second.size() > 0) {
            std::vector<std::string> files(file.second.begin(), file.second.end());
            result.push_back(files);
        }
    }
    return result;
}
