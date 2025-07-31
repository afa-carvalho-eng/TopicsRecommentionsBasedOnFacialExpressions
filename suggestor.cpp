#include "suggestor.hpp"
#include "sentiment.hpp"

Suggestor::Suggestor(const std::vector<std::string>& texts, Mood mood)
    : texts(texts), mood(mood) {}

std::string Suggestor::suggest() const {
    if (texts.empty()) {
        return "No suggestions available at the moment.";
    }

    std::string match;
    for (const auto& text : texts) {
        Sentiment s = SentimentAnalyzer::analyze(text);
        if ((mood == Mood::Happy && s == Sentiment::Positive) ||
            (mood == Mood::Sad && s == Sentiment::Negative)) {
            match = text;
            break;
        }
    }

    if (match.empty()) {
        match = texts[0];  // fallback
    }

    std::string intro = (mood == Mood::Happy)
        ? "How about this cheerful topic?"
        : "Perhaps this resonates with your current thoughts.";

    return "💡 " + intro + "\n" + match;
}
