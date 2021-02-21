#pragma once
#include <map>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <unordered_map>

/** @warning: FOR LEARNING PURPOSES YOU ARE NOT ALLOWED TO USE LOOPS!*/

/** @todo Must compare two strings without case checking*/
struct NoCaseComparator
{
    bool operator()(const std::string& lhs, const std::string& rhs) const
    {
    }
};

/** Group types */
enum class CVGroup
{
    CPP,
    Java,
    GeneralDev
};

using keywords = std::set<std::string, NoCaseComparator>;
using skillMatrix = std::map<CVGroup, keywords>;
using groupsRatio = std::multimap<size_t /*percents*/, CVGroup>;

/**
 * @todo Implement filtering out special characters in text
 * @param source - text to process
 * @return Returns text that contains only alphanumerical symbols,
 * spaces and "exceptional" symbols: +, #, -
 * must replace special characters with spaces
 */
std::string getPlainText(const std::string& source);

/**
 * @todo Splits words by spaces
 * @param source - text to split
 * @return set of unique keywords
 */
keywords splitOnWords(const std::string& source);

/**
 * @brief Implements cleanup for the text (original -> plain -> split)
 * @param text - text from CV
 * @return unique keywords found in CV
 */
keywords parseText(const std::string& text);

/**
 * This function must build skill matrix fom processed cv text
 * So, in general, algorithm should get keywords from the cv, and
 * "classify" them.
 * For example "C++ developer with 5 years of STL experience."
 * C++ sink in result matrix will contain 2 entries(based on general matrix): C++, STL
 */

/**
 * @todo Implement function that builds skill matrix from processed cv text
 * Steps are:
 * 1. Get keywords
 * 2. Classify keywords
 *
 * @example "C++ developer with 5 years of STL experience."
 * C++ sink in result matrix will contain 2 entries(based on general matrix): C++, STL
 *
 * @param cvWords - parsed keywords from CV
 * @param generalMatrix - prepared "professional words" list
 *
 * @return Pairs of "Speciality" - "Found professional words"
 */
skillMatrix buildSkillsMatrix(const keywords& cvWords,
                              const skillMatrix& generalMatrix);

/**
 * @todo Implement function that will sort speciality probability by CV.
 * Results are sorted by percents of matching words.
 *
 * @param generalMatrix - prepared "professional words" list
 * @param cvMatrix - parsed from cv "found professional words" list
 *
 * @example Row C++ contains 2 tags, and general matrix contains 4 tags,
 * then result will have {50, CPP} entry
 *
 * @return Returns matrix rows ratio
 */
groupsRatio getGroupsRelation(const skillMatrix& generalMatrix,
                              const skillMatrix& cvMatrix);

/**
 * @todo Implement function that will return CV speciality or specialities
 * @param relations CV group relation
 * @return group with maximum ratio (if several equal ratio - several groups)
 */
std::vector<CVGroup> getPossibleCVGroups(const groupsRatio& relations);

/**
 * @warning BONUS TASK:
 * COUNT OCCURENCIES OF EACH WORD IN A RESULT MATRIX AND CALCULATE EACH GROUP "WEIGHT"
 * WEIGHT IS DEFINED BY A SUM OF WORDS OCCURENCIES IN EACH ROW
 * For example, row "CPP: C++ (7 times), C (3 times), STL (1 time)"
 * Weight will be 11
 */
std::unordered_map<CVGroup, size_t> getGroupWeights(const std::string& text, const skillMatrix& generalMatrix);
