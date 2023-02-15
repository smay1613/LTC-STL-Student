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

std::vector<std::string> listFiles(const std::string& directory) {
    std::vector<std::string> listFiles;
    for (auto const& dir_entry : fs::recursive_directory_iterator(directory)) {
        if (fs::is_regular_file(dir_entry)) {
            listFiles.push_back(dir_entry.path());
        }
    }
    return listFiles;
}

void removeUniqueGroups(filtering_map& filteredData) {
    auto iter = filteredData.begin();
    while (iter != filteredData.end()) {
        if (iter->second.size() < 2) {
            iter = filteredData.erase(iter);
        } else {
            iter++;
        }
    }
}

std::vector<std::string> flattenGrouped (const filtering_map& grouped) {
    std::vector<std::string> flattenGroups;
    for (auto const& pair : grouped) {
        flattenGroups.insert(flattenGroups.end(), pair.second.begin(), pair.second.end());
    }
    return flattenGroups;
}

/** @todo Implement filtering files by different buckets by specified criteria*/
template<class FilterCriteria>
filtering_map filter(const std::vector<std::string>& files, FilterCriteria filter)
{
    filtering_map filteredFiles;
    for (auto const& file : files) {
        filteredFiles[filter(file)].push_back(file);
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

std::vector<std::vector<std::string>> findDuplicates(const std::string &rootPath)
{
    // filter by size
    filtering_map filesBySize = groupDuplicates(listFiles(rootPath),
        [](const std::string& file) { return fs::file_size(file); });

    std::vector<std::string> filesList = flattenGrouped(filesBySize);

    // filter by content
    filtering_map filesByContent = groupDuplicates(filesList,
        [](const std::string& file) { return xx_hash(file); });

    // flatten
    std::vector<std::vector<std::string>> filesGroupedByContent;
    for (auto const& fileAndContent : filesByContent) {
        if (fileAndContent.second.size() > 0) {
            std::vector<std::string> files(fileAndContent.second.begin(), fileAndContent.second.end());
            filesGroupedByContent.push_back(files);
        }
    }
    return filesGroupedByContent;
}
