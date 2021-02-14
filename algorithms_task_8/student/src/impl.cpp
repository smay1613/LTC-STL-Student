#include "impl.h"

skillMatrix buildSkillsMatrix(const keywords &cvWords, const skillMatrix &generalMatrix)
{
    skillMatrix cvMatrix;

    // convert from general matrix to cv matrix by cvWords

    return cvMatrix;
}

groupsRatio getGroupsRelation(const skillMatrix &generalMatrix, const skillMatrix &cvMatrix)
{
    groupsRatio ratios;
    // ratio is relation between cv matrix row and general matrix row
    using row = std::pair<CVGroup, keywords>;

    return ratios;
}

std::vector<CVGroup> getPossibleCVGroups(const groupsRatio& relations)
{
}

keywords parseText(const std::string &text)
{
    std::string keywordsCloud {getPlainText(text)};
    return splitOnWords(keywordsCloud);
}

keywords splitOnWords(const std::string &source)
{
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

    return textWithOnlyAlphaNumericalData;
}
