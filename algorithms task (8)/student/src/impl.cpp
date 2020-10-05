#include "impl.h"

skillMatrix buildSkillsMatrix(const keywords &cvWords, const skillMatrix &generalMatrix)
{
    skillMatrix cvMatrix;

    auto transformator = [&cvWords](const skillMatrix::value_type& value) -> skillMatrix::value_type
    {
        keywords filteredWords;
        std::set_intersection(cvWords.begin(), cvWords.end(),
                              value.second.begin(), value.second.end(),
                              std::inserter(filteredWords, filteredWords.end()),
                              keywords::key_compare{});
        return { value.first, std::move(filteredWords) };
    };
    std::transform(generalMatrix.begin(), generalMatrix.end(),
                   std::inserter(cvMatrix, cvMatrix.end()),
                   transformator);
    return cvMatrix;
}

groupsRatio getGroupsRelation(const skillMatrix &generalMatrix, const skillMatrix &cvMatrix)
{
    groupsRatio ratios;
    // ratio is relation between cv matrix row and general matrix row
    using row = std::pair<CVGroup, keywords>;

    static_assert(!std::is_same<row, skillMatrix::value_type>::value, "row is not skillMatrix::value_type");

    auto transformator = [&generalMatrix](const skillMatrix::value_type& value) -> groupsRatio::value_type
    {
        const size_t generalGroupSize = generalMatrix.at(value.first).size();
        return { generalGroupSize != 0 ? (100 * value.second.size()) / generalGroupSize : 0,
                 value.first };
    };
    std::transform(cvMatrix.begin(), cvMatrix.end(),
                   std::inserter(ratios, ratios.end()),
                   transformator);
    return ratios;
}

std::vector<CVGroup> getPossibleCVGroups(const groupsRatio& relations)
{
    std::vector<CVGroup> specialities;

    auto transformator = [](const groupsRatio::value_type& value) -> CVGroup
    {
        return value.second;
    };
    const size_t maxRatio = !relations.empty() ? relations.rbegin()->first : 0;

    std::transform(relations.lower_bound(maxRatio), relations.end(),
                   std::back_inserter(specialities),
                   transformator);
    return specialities;
}

keywords parseText(const std::string &text)
{
    std::string keywordsCloud {getPlainText(text)};
    return splitOnWords(keywordsCloud);
}

keywords splitOnWords(const std::string &source)
{
    keywords words;

    std::istringstream stream(source);
    std::copy_if(std::istream_iterator<std::string>{stream},
                 std::istream_iterator<std::string>{},
                 std::inserter(words, words.end()),
                 [](const std::string& word) { return !word.empty(); });
    return words;
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

    std::replace_copy_if(source.begin(), source.end(),
                         std::back_inserter(textWithOnlyAlphaNumericalData),
                         isSpecial,
                         ' ');
    return textWithOnlyAlphaNumericalData;
}

std::unordered_map<CVGroup, size_t>
getGroupWeights(const std::string& text, const skillMatrix& generalMatrix)
{
    std::map<std::string, size_t, NoCaseComparator> wordFrequencies;

    auto incrementWordFrequency = [&wordFrequencies](const std::string& word)
    {
        if (!word.empty())
        {
            ++(wordFrequencies[word]);
        }
    };
    std::istringstream stream(getPlainText(text));
    std::for_each(std::istream_iterator<std::string>{stream},
                  std::istream_iterator<std::string>{},
                  incrementWordFrequency);

    std::unordered_map<CVGroup, size_t> weights;

    auto accumulator = [&wordFrequencies](size_t weight, const std::string& word)
    {
        const auto foundIt = wordFrequencies.find(word);
        return weight + (foundIt != wordFrequencies.end() ? foundIt->second : 0);
    };
    auto transformator = [&accumulator](const skillMatrix::value_type& value) -> decltype(weights)::value_type
    {
        return { value.first,
                 std::accumulate(value.second.begin(), value.second.end(), 0, accumulator) };
    };
    std::transform(generalMatrix.begin(), generalMatrix.end(),
                   std::inserter(weights, weights.end()),
                   transformator);
    return weights;
}
