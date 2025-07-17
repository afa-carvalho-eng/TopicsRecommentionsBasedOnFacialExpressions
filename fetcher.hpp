// fetcher.hpp
#ifndef FETCHER_HPP
#define FETCHER_HPP

#include <string>
#include <vector>

class NewsFetcher {
public:
    NewsFetcher(const std::string& apiKey, const std::string& country = "us", const std::string& category = "general");
    std::vector<std::string> fetch(int pageSize = 10);

private:
    std::string apiKey;
    std::string country;
    std::string category;
};

#endif
