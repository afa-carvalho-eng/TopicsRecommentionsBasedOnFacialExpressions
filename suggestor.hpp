#ifndef SUGGESTOR_HPP
#define SUGGESTOR_HPP

#include <string>
#include <vector>

enum class Mood { Sad, Happy, Neutral };

class Suggestor {
public:
    Suggestor(const std::vector<std::string>& texts, Mood mood = Mood::Happy);
    std::string suggest() const;

private:
    std::vector<std::string> texts;
    Mood mood;
};

#endif
