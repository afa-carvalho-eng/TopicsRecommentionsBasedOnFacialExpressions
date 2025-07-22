// suggestor.cpp
#include "suggestor.hpp"
#include <iostream>

Suggestor::Suggestor(const std::vector<std::string>& headlines, Mood mood)
    : headlines(headlines), mood(mood) {}

std::string Suggestor::suggest() {
    if (headlines.empty()) {
        return "No trending topics found right now—maybe check again soon!";
    }

    // Simple: pick the first headline (or random headline)
    std::string selectedHeadline = headlines[0];

    // Optionally: choose based on mood (simplified)
    if (mood == Mood::Happy && headlines.size() > 1) {
        selectedHeadline = headlines[1]; // naive mood-specific choice
    }

    std::string moodIntro = (mood == Mood::Happy)
        ? "How about this cheerful topic?"
        : "Perhaps reflecting on this might resonate with your feelings.";

    return "💡 " + moodIntro + "\n**" + selectedHeadline + "**";
}
