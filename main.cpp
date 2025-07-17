// main.cpp
#include <iostream>
#include <vector>
#include "fetcher.hpp"
#include "analyzer.hpp"
#include "suggestor.hpp"

int main() {
    std::string apiKey = "YOUR_NEWSAPI_KEY";  // Replace with your API key
    
    NewsFetcher fetcher(apiKey);
    std::vector<std::string> headlines = fetcher.fetch(10);

    TopicAnalyzer analyzer(headlines);
    std::vector<std::string> keywords = analyzer.extractKeywords(5);

    Suggestor suggestor(keywords);
    std::string suggestion = suggestor.suggest();

    std::cout << "📰 Latest headlines:\n";
    for (const auto& headline : headlines) {
        std::cout << " - " << headline << "\n";
    }

    std::cout << "\n💡 Topic suggestion:\n" << suggestion << "\n";
    return 0;
}
