#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <vector>
#include <string>
#include <unordered_set>

class TopicAnalyzer {
public:
    TopicAnalyzer(const std::vector<std::string>& inputTexts);
    std::vector<std::string> extractKeywords(int topN = 5) const;

private:
    std::vector<std::string> texts;
    static const std::unordered_set<std::string> stopwords;
};

#endif
