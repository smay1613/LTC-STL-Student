#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "xxhash.h"

using filtering_map = std::unordered_map<size_t, std::vector<std::string>>;

/** @todo With help of std filesystem, lists all regular files under specified directory recursively*/
std::vector<std::string> listFiles(const std::string& directory){
    std::vector<std::string> file_list;

    for (const auto& dir_entry : std::filesystem::recursive_directory_iterator(directory)){

        if(dir_entry.is_regular_file()){

            file_list.push_back(dir_entry.path());

        } else{
            
            auto sub_files = listFiles(dir_entry.path());
        }
    }

    return file_list;
}

/** @todo Implement function that will remove group in if it has only one or zero elements */
void removeUniqueGroups(filtering_map& filteredData){

    for( auto group = filteredData.begin(), last = filteredData.end();  group != last;){
        
        if(group->second.size() <= 1){

            group = filteredData.erase(group);
        } else {
            group++;
        }
    }
}

/** @todo Implement function that will transform map to a vector */
std::vector<std::string> flattenGrouped (const filtering_map& grouped){

    std::vector<std::string> flattened;

    for( auto group : grouped){
        for( auto s : group.second){
            flattened.push_back(s);
        }      
    }

    return flattened;
}

/**
 * @todo Implement function that fill find duplicated files under the directory recursively
 * @param rootPath - directory to check
 * @return list of duplicated files, grouped by content
 */
std::vector<std::vector<std::string>> findDuplicates(const std::string& rootPath);
