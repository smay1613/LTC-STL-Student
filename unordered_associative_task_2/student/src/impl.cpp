#include "impl.h"
#include <experimental/filesystem>
#include <fstream>
#include <numeric>
#include "xxhash.h"
#include <iostream>
#include <functional>

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

struct FilterBySize{
    size_t operator()(std::string path){
        return fs::file_size(path);
    }
};

struct FilterByHash{
    size_t operator()(std::string path){
        return xx_hash(path);
    }
};

/** @todo Implement filtering files by different buckets by specified criteria*/
template<class FilterCriteria>
filtering_map filter(const std::vector<std::string>& files, FilterCriteria filter)
{
    filtering_map unique;
    
    for(auto path : files){

        unique[filter(path)].push_back(path);
    }
    return unique;
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
    filtering_map by_size = groupDuplicates(listFiles(rootPath), FilterBySize());

    // flatten
    std::vector<std::string> duplicated_file_list = flattenGrouped(by_size);

    // filter by content
    filtering_map by_hash = groupDuplicates(duplicated_file_list, FilterByHash());
    
    std::vector<std::vector<std::string>> duplicated;
    for( const auto& group : by_hash){

        duplicated.push_back(group.second);
    }

    return duplicated;
}
