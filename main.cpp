#include <iostream>
#include <vector>
#include "fetcher.hpp"
#include "analyzer.hpp"
#include "suggestor.hpp"
#include "emotion_detector.hpp"
#include <chrono>
#include <thread>
#include <unistd.h>  

int main() {
    const std::string apiKey = "76cbef8f35eb42a2b4c2bf8ec332a7f7";  // Replace with your API key
    Mood userMood = Mood::Neutral;
    
    NewsFetcher fetcher(apiKey);
    
    while (true) {
        DetectedEmotion detected = EmotionDetector("facial_expression_recognition_mobilefacenet_2022july.onnx").detectEmotion();
        switch (detected) 
        {
           case DetectedEmotion::Happy: userMood = Mood::Happy; break;
           case DetectedEmotion::Sad: userMood = Mood::Sad; break;
           case DetectedEmotion::Neutral: default: userMood = Mood::Sad; break; // Neutral as fallback
        }


        
        std::cout << "Detected mood: " 
          << (userMood == Mood::Happy ? "Happy" : "Sad") << "\n";

        std::vector<std::string> headlines = fetcher.fetch(10);

        Suggestor suggestor(headlines, userMood);
        std::string suggestion = suggestor.suggest();
        std::cout << "\n💬 Topic suggestion:\n" << suggestor.suggest() << "\n";

        // Step 3: Still analyze keywords, but print separately
        TopicAnalyzer analyzer(headlines);
        std::vector<std::string> keywords = analyzer.extractKeywords(5);
        std::cout << "\n🔍 Trending keywords:\n";
        for (const auto& keyword : keywords)
            std::cout << " - " << keyword << "\n";
    
        sleep(1);
    }

    return 0;
}
