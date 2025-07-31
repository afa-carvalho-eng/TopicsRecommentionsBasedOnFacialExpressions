#include "analyzer.hpp"
#include <sstream>
#include <algorithm>
#include <map>
#include <cctype>

const std::unordered_set<std::string> TopicAnalyzer::stopwords = {
    "the", "and", "or", "but", "a", "an", "of", "to", "in", "on", "for", "with",
    "at", "from", "by", "this", "that", "is", "it", "are", "was", "be", "as", "not",
    "news", "york", "times", "update", "report", "today", "breaking", "live"
};

TopicAnalyzer::TopicAnalyzer(const std::vector<std::string>& inputTexts) : texts(inputTexts) {}

std::vector<std::string> TopicAnalyzer::extractKeywords(int topN) const {
    std::map<std::string, int> wordCount;

    for (const auto& text : texts) {
        std::istringstream stream(text);
        std::string word;
        while (stream >> word) {
            word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);

            if (!word.empty() && stopwords.find(word) == stopwords.end()) {
                wordCount[word]++;
            }
        }
    }

    std::vector<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());
    std::sort(sortedWords.begin(), sortedWords.end(), [](auto& a, auto& b) {
        return b.second > a.second;
    });

    std::vector<std::string> keywords;
    for (const auto& [word, count] : sortedWords) {
        if (word.length() > 2 && !std::all_of(word.begin(), word.end(), ::isdigit)) {
            keywords.push_back(word);
        }
        if (keywords.size() >= static_cast<size_t>(topN)) break;
    }

    return keywords;
}
