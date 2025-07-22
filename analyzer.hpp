// analyzer.hpp
#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <vector>
#include <string>

class TopicAnalyzer {
public:
    TopicAnalyzer(const std::vector<std::string>& headlines);
    std::vector<std::string> extractKeywords(int topN = 5);

private:
    std::vector<std::string> headlines;
    const std::vector<std::string> stopwords = {
    "the", "and", "or", "but", "a", "an", "of", "to", "in", "on", "for", "with",
    "at", "from", "by", "this", "that", "is", "it", "are", "was", "be", "as", "not",
    "news", "york", "times", "update", "report", "today", "breaking", "live"
    };

};

#endif
