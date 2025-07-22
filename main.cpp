// main.cpp
#include <iostream>
#include <vector>
#include "fetcher.hpp"
#include "analyzer.hpp"
#include "suggestor.hpp"
#include <unistd.h>   

int main() {
    while (true)
    {
        std::string apiKey = "76cbef8f35eb42a2b4c2bf8ec332a7f7";  // Replace with your API key
        
        NewsFetcher fetcher(apiKey);
        std::vector<std::string> headlines = fetcher.fetch(10);
        
        TopicAnalyzer analyzer(headlines);
        std::vector<std::string> keywords = analyzer.extractKeywords(5);
        
        Mood userMood = Mood::Sad; // Or Mood::Happy, based on user input
        Suggestor suggestor(keywords, userMood);
        std::string suggestion = suggestor.suggest();

        std::cout << "📰 Latest headlines:\n";
        for (const auto& headline : headlines) {
            std::cout << " - " << headline << "\n";
        }

        std::cout << "\n💡 Topic suggestion:\n" << suggestion << "\n";
        
        sleep(3);
    }

    return 0;
}
