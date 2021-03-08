#include "impl.h"
using namespace std;
using row = std::pair<CVGroup, keywords>;

skillMatrix buildSkillsMatrix(const keywords &cvWords, const skillMatrix &generalMatrix)
{
    skillMatrix cvMatrix;

    // convert from general matrix to cv matrix by cvWords
    transform(generalMatrix.begin(), generalMatrix.end(),
              std::inserter(cvMatrix, cvMatrix.begin()) ,
              [&cvWords](row const & skillRow) {
                  keywords skillKeywords;

                  set_intersection(cvWords.begin(), cvWords.end(),
                                   skillRow.second.begin(), skillRow.second.end(),
                                   inserter(skillKeywords, skillKeywords.begin()),
                                   NoCaseComparator());

                  return std::make_pair(skillRow.first, skillKeywords);
    });

    return cvMatrix;
}

groupsRatio getGroupsRelation(const skillMatrix &generalMatrix, const skillMatrix &cvMatrix)
{
    groupsRatio ratios;
    // ratio is relation between cv matrix row and general matrix row

    transform(generalMatrix.begin(), generalMatrix.end(),
                  cvMatrix.begin(),
                  std::inserter(ratios,ratios.begin()),
                  [](row const & skillRowGeneral, row const & skillRowCV) {
                      auto words = skillRowCV.second;
                      auto ratio =  (words.size()/ skillRowGeneral.second.size()) * 100;
                      return std::make_pair(ratio, skillRowGeneral.first);
    });

    return ratios;
}

std::vector<CVGroup> getPossibleCVGroups(const groupsRatio& relations)
{
    std::vector<CVGroup> possibleCVGroups;

    auto max = max_element(relations.begin(), relations.end());   

    auto maxRange = relations.equal_range(max->first);

    using relation_type = std::pair<size_t, CVGroup> const &;
    transform(maxRange.first, maxRange.second,
              back_inserter(possibleCVGroups),
              [](relation_type relation) {
                 return relation.second;
    });

    return possibleCVGroups;
}

keywords parseText(const std::string &text)
{
    std::string keywordsCloud {getPlainText(text)};
    return splitOnWords(keywordsCloud);
}

keywords splitOnWords(const std::string &source)
{
    stringstream input{source};

    return {istream_iterator<string>(input), istream_iterator<string>()};
}

std::string getPlainText(const std::string &source)
{
    static const std::string exceptionalChars {"+#-"};
    std::string textWithOnlyAlphaNumericalData;
    textWithOnlyAlphaNumericalData.reserve(source.size());

    auto isSpecial = [](const char symbol) {
        return !std::isalnum(symbol)
                && exceptionalChars.find(symbol) == std::string::npos;
    };
    /** @todo ADD PROCESSING HERE */
    std::replace_copy_if(source.cbegin(), source.cend(),
                         back_inserter(textWithOnlyAlphaNumericalData), isSpecial, ' ');

    return textWithOnlyAlphaNumericalData;
}

std::unordered_map<CVGroup, size_t> getGroupWeights(const std::string& text, const skillMatrix& generalMatrix)
{
    std::unordered_map<CVGroup, size_t> groupWeights;

    stringstream input{getPlainText(text)};
    std::vector<string> splited {istream_iterator<string>(input), istream_iterator<string>()};

    auto weightCounter = [](vector<string> const& splited, row const & skillRow ) {
        return count_if(splited.begin(), splited.end(), [&skillRow](const std::string & key) {
            auto match = skillRow.second.find(key);
            return match != skillRow.second.end();
        });
    };

    transform(generalMatrix.begin(), generalMatrix.end(),
              inserter(groupWeights, groupWeights.begin()),
              [&splited, &weightCounter](row const & skillRow){
                  return std::make_pair(skillRow.first, weightCounter(splited,skillRow));
    });

    return groupWeights;
}
