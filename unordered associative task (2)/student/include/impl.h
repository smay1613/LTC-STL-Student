#pragma once
#include <vector>
#include <string>
#include <unordered_map>

using filtering_map = std::unordered_map<size_t, std::vector<std::string>>;

/** @todo With help of std filesystem, lists all regular files under specified directory recursively*/
std::vector<std::string> listFiles(const std::string& directory);

/** @todo Implement function that will remove group in if it has only one or zero elements */
void removeUniqueGroups(filtering_map& filteredData);

/** @todo Implement function that will transform map to a vector */
std::vector<std::string> flattenGrouped (const filtering_map& grouped);

/**
 * @todo Implement function that fill find duplicated files under the directory recursively
 * @param rootPath - directory to check
 * @return list of duplicated files, grouped by content
 */
std::vector<std::vector<std::string>> findDuplicates(const std::string& rootPath);
