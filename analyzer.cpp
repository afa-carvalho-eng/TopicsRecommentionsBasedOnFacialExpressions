// analyzer.cpp
#include "analyzer.hpp"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <iostream>

TopicAnalyzer::TopicAnalyzer(const std::vector<std::string>& headlines) : headlines(headlines) {}

std::vector<std::string> TopicAnalyzer::extractKeywords(int topN) {
    std::map<std::string, int> wordCount;

    for (const auto& headline : headlines) {
        std::istringstream stream(headline);
        std::string word;
        while (stream >> word) {
            word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);

            if (std::find(stopwords.begin(), stopwords.end(), word) == stopwords.end()) {
                wordCount[word]++;
            }
        }
    }

    std::vector<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());
    std::sort(sortedWords.begin(), sortedWords.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
    });

    std::vector<std::string> keywords;
    for (const auto& pair : sortedWords) {
        if (pair.first.length() > 2 &&  // filter short words
            !pair.first.empty() &&
            !std::all_of(pair.first.begin(), pair.first.end(), ::isdigit)) {
            keywords.push_back(pair.first);
        }
        if (keywords.size() >= topN) break;
    }

    return keywords;
}
