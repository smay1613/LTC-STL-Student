#include "impl.h"
#include "xxhash.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

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

auto filesize = [](const std::string& file) {
    std::ifstream stream { file };
    if (!stream) {
        std::cerr << "File " << file << " can't be opened" << std::endl;
        return 0ul;
    }
    return fs::file_size(file);
};

/** @todo Implement filtering files by different buckets by specified criteria */
template <class FilterCriteria>
filtering_map filter(const std::vector<std::string>& files, FilterCriteria filter)
{
    filtering_map result;
    for (auto const& file : files) {
        auto criteria = filter(file);
    }
    return result;
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
    std::vector<std::string> files;
    for (auto& p : fs::directory_iterator(directory)) {
        std::cout << p.path().filename().string() << '\n';
        files.push_back(p.path());
    }
    return files;
}

/** @todo Implement function that will remove group in if it has only one or zero elements */
void removeUniqueGroups(filtering_map& filteredData)
{
}

/** @todo Implement function that will transform map to a vector */
std::vector<std::string> flattenGrouped(const filtering_map& grouped)
{
    std::vector<std::string> result;
    return result;
}

std::vector<std::vector<std::string>> findDuplicates(const std::string& rootPath)
{
    std::cout << "std::vector<std::vector<std::string>> findDuplicates(const std::string& rootPath)" << std::endl;
    std::cout << rootPath << std::endl;

    auto files = listFiles(rootPath);

    // filter by size
    filtering_map filtered_by_size = filter<>(files, filesize);
    // filter by content
    filtering_map filtered_by_content = filter<>(files, xx_hash);
    // flatten

    std::vector<std::vector<std::string>> result = { flattenGrouped(filtered_by_size), flattenGrouped(filtered_by_content) };
    return result;
}
