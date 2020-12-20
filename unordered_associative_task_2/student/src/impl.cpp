#include "impl.h"
#include "xxhash.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

// use this for hashing
auto xx_hash = [](const std::string& file) {
    std::ifstream stream { file };

    if (!stream) {
        std::cerr << "File " << file << " can't be opened" << std::endl;
        return xxh::hash_t<64> {};
    }

    const auto length = fs::file_size(file);
    std::vector<char> buffer(length);
    stream.read(buffer.data(), length);

    return xxh::xxhash<64>(buffer);
};

auto xx_file_size = [](const std::string& file) {
    std::ifstream stream { file };
    if (!stream) {
        std::cerr << "File " << file << " can't be opened" << std::endl;
        return 0ul;
    }
    return fs::file_size(file);
};

struct FileObject {
    explicit FileObject(const std::string& name)
        : filename { name }
        , size { xx_file_size(filename) }
        , hash { xx_hash(filename) }
    {
    }

    bool operator<(const FileObject& rhs)
    {
        return std::tie(size, hash) < std::tie(rhs.size, rhs.hash);
    }

    std::string filename;
    size_t size;
    size_t hash;
};

/** @todo Implement filtering files by different buckets by specified criteria */
template <class FilterCriteria>
filtering_map filter(const std::vector<std::string>& files, FilterCriteria filter)
{
    filtering_map filteredFiles;
    for (auto const& fileName : files) {
        filteredFiles[filter(fileName)].push_back(fileName);
    }
    return filteredFiles;
}

/** @note HELPER */
template <class Filter>
filtering_map groupDuplicates(const std::vector<std::string>& dataSource, Filter filterCriteria)
{
    auto grouped = filter(dataSource, filterCriteria);
    removeUniqueGroups(grouped);
    return grouped;
}

/** @todo With help of std filesystem, lists all regular files under specified directory recursively*/
std::vector<std::string> listFiles(const std::string& directory)
{
    std::vector<std::string> fileNames;
    for (auto& p : fs::recursive_directory_iterator(directory)) {
        if (fs::is_regular_file(p)) {
            fileNames.push_back(p.path().string());
        }
    }
    return fileNames;
}

/** @todo Implement function that will remove group in if it has only one or zero elements */
void removeUniqueGroups(filtering_map& filteredData)
{
    for (auto it = filteredData.begin(); it != filteredData.end();) {
        if (it->second.size() == 1)
            it = filteredData.erase(it);
        else
            ++it;
    }
}

/** @todo Implement function that will transform map to a vector */
std::vector<std::vector<std::string>> flattenGrouped(const filtering_map& grouped)
{
    std::vector<std::vector<std::string>> groups;
    for (auto const& group : grouped) {
        if (!group.second.empty()) {
            std::vector<std::string> files(group.second.begin(), group.second.end());
            groups.emplace_back(files);
        }
    }
    return groups;
}

std::vector<std::vector<std::string>> findDuplicates(const std::string& rootPath)
{
    auto files = listFiles(rootPath);

    // not filtered by size!
    // filter by content
    auto groupped_duplicates = groupDuplicates(files, xx_hash);

    // remove unique groups
    removeUniqueGroups(groupped_duplicates);

    // flatten
    std::vector<std::vector<std::string>> duplicates = flattenGrouped(groupped_duplicates);

    return duplicates;
}
