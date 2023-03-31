#pragma once
#include <vector>
#include <string>
#include <unordered_map>

using filtering_map = std::unordered_map<size_t, std::vector<std::string>>;

/** @todo With help of std filesystem, lists all regular files under specified directory recursively*/
std::vector<std::string> listFiles(const std::string& directory) {
    
    std::vector<std::string> file_list;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {

        if (entry.is_regular_file()) {
            file_list.push_back(entry.path());
        }
    }

    return file_list;
}
/** @todo Implement function that will remove group in if it has only one or zero elements */
void removeUniqueGroups(filtering_map& filteredData) {
    auto group = filteredData.begin();
    while ( group != last;) {

        if (group->second.size() <= 1) {
            group = filteredData.erase(group);
        }
        else {
            group++;
        }
    }
}

/** @todo Implement function that will transform map to a vector */
std::vector<std::string> flattenGrouped (const filtering_map& grouped) {

    std::vector<std::string> result;
    for (const auto& group : grouped) {
        result.insert(result.end(), group.second.begin(), group.second.end());
    }

    return result;
}

/**
 * @todo Implement function that fill find duplicated files under the directory recursively
 * @param rootPath - directory to check
 * @return list of duplicated files, grouped by content
 */
std::vector<std::vector<std::string>> findDuplicates(const std::string& rootPath);
