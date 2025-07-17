// suggestor.cpp
#include "suggestor.hpp"
#include <iostream>

Suggestor::Suggestor(const std::vector<std::string>& keywords) : keywords(keywords) {}

std::string Suggestor::suggest() {
    if (keywords.empty()) {
        return "No trending topics found right now—maybe check again soon!";
    }

    std::string primary = keywords[0];
    std::string others = keywords.size() > 1 ? ", " + keywords[1] : "";

    return "How about discussing **" + primary + "**? It's trending now along with" + others + ".";
}
