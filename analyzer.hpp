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
    std::vector<std::string> stopwords = {
        "about", "which", "their", "these", "should", "since", "years", "business", "people", "before"
    };
};

#endif
