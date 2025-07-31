#include "sentiment.hpp"
#include <unordered_set>
#include <sstream>
#include <algorithm>

static const std::unordered_set<std::string> positiveWords = {
    "win", "hope", "joy", "happy", "success", "growth", "love", "peace", "cheer", "rise", "positive", "gain"
};

static const std::unordered_set<std::string> negativeWords = {
    "war", "death", "crisis", "decline", "attack", "fail", "sad", "loss", "pain", "suffer", "fall", "negative", "violence"
};

Sentiment SentimentAnalyzer::analyze(const std::string& text) {
    int score = 0;
    std::istringstream iss(text);
    std::string word;

    while (iss >> word) {
        // Remove punctuation and convert to lowercase
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (positiveWords.count(word)) score++;
        if (negativeWords.count(word)) score--;
    }

    if (score > 0) return Sentiment::Positive;
    if (score < 0) return Sentiment::Negative;
    return Sentiment::Neutral;
}
