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
    filtering_map unique;

    for(auto path : files){
        std::size_t key;

        if(filter){

            std::ifstream stream {path};

            if (!stream)
            {
                std::cerr << "File " << path << " can't be opened" << std::endl;
            }

            key = (!stream)? 0 : fs::file_size(path);
        } else {

            key = xx_hash(path);
        }

        std::vector<std::string> none = {};
        unique.try_emplace(key, none);
        unique[key].push_back(path);
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
    filtering_map by_size = groupDuplicates(listFiles(rootPath), true);

    // flatten
    std::vector<std::string> duplicated_file_list = flattenGrouped(by_size);

    // filter by content
    filtering_map by_hash = groupDuplicates(duplicated_file_list, false);
    
    std::vector<std::vector<std::string>> duplicated;
    for( auto group : by_hash){

        duplicated.push_back(group.second);
    }

    return duplicated;
}
