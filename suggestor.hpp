// suggestor.hpp
#ifndef SUGGESTOR_HPP
#define SUGGESTOR_HPP

#include <vector>
#include <string>

class Suggestor {
public:
    Suggestor(const std::vector<std::string>& keywords);
    std::string suggest();

private:
    std::vector<std::string> keywords;
};

#endif
