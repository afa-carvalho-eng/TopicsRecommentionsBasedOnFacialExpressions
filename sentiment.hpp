#ifndef SENTIMENT_HPP
#define SENTIMENT_HPP

#include <string>

enum class Sentiment { Positive, Negative, Neutral };

class SentimentAnalyzer {
public:
    static Sentiment analyze(const std::string& text);
};

#endif
