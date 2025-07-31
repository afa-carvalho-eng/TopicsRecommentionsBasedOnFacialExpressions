#ifndef FETCHER_HPP
#define FETCHER_HPP

#include <string>
#include <vector>

class NewsFetcher {
public:
    NewsFetcher(std::string apiKey, std::string country = "us", std::string category = "general");
    std::vector<std::string> fetch(int pageSize = 10);

private:
    std::string apiKey;
    std::string country;
    std::string category;

    std::string constructUrl(int pageSize) const;
};

#endif
