#include "../include/impl.h"

#include <iostream>


skillMatrix buildSkillsMatrix(const keywords &cvWords, const skillMatrix &generalMatrix)
{
    skillMatrix cvMatrix;

    // convert from general matrix to cv matrix by cvWords
    auto groups = {CVGroup::CPP, CVGroup::GeneralDev, CVGroup::Java};
    std::for_each(groups.begin(), groups.end(), [&](auto g){
        cvMatrix[g] = {};
        std::set_intersection(cvWords.begin(), cvWords.end(), 
            generalMatrix.at(g).begin(), generalMatrix.at(g).end(), 
            std::inserter(cvMatrix[g], cvMatrix[g].begin()), 
            NoCaseComparator());
    });
    return cvMatrix;
}

groupsRatio getGroupsRelation(const skillMatrix &generalMatrix, const skillMatrix &cvMatrix)
{
    groupsRatio ratios;
    // ratio is relation between cv matrix row and general matrix row
    using row = std::pair<CVGroup, keywords>;
    auto groups = {CVGroup::CPP, CVGroup::GeneralDev, CVGroup::Java};
    
    std::for_each(groups.begin(), groups.end(), [&](auto g){
        ratios.emplace(cvMatrix.at(g).size() / generalMatrix.at(g).size(), g);
    });

    return ratios;
}

std::vector<CVGroup> getPossibleCVGroups(const groupsRatio& relations)
{
    std::vector<CVGroup> most_qualified;
    auto start = relations.lower_bound(std::prev(relations.end())->first);
    std::transform( start, relations.end(), std::back_inserter(most_qualified),
        [](auto &kv){ 
            return kv.second;
        });
    return most_qualified; 
}

keywords parseText(const std::string &text)
{
    std::string keywordsCloud {getPlainText(text)};
    return splitOnWords(keywordsCloud);
}

keywords splitOnWords(const std::string &source)
{
    std::stringstream ss(source);
    std::vector<std::string> aux((std::istream_iterator<std::string>(ss)), std::istream_iterator<std::string>());
    keywords output(aux.begin(), aux.end());

    return output;
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
    std::transform(source.begin(), source.end(), std::back_inserter(textWithOnlyAlphaNumericalData), 
    [isSpecial](auto c){
        if(isSpecial(c)){
            return ' ';
        }
        return c;
    });
    return textWithOnlyAlphaNumericalData;
}
