// suggestor.hpp
#include <vector>
#include <string>

enum class Mood { Sad, Happy };

class Suggestor {
public:
    Suggestor(const std::vector<std::string>& headlines, Mood mood);

    std::string suggest();

private:
    std::vector<std::string> headlines;
    Mood mood;
};
