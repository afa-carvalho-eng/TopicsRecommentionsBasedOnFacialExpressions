#include "fetcher.hpp"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>

NewsFetcher::NewsFetcher(std::string apiKey, std::string country, std::string category)
    : apiKey(std::move(apiKey)), country(std::move(country)), category(std::move(category)) {}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string NewsFetcher::constructUrl(int pageSize) const {
    return "https://newsapi.org/v2/top-headlines?country=" + country +
           "&category=" + category + "&pageSize=" + std::to_string(pageSize) +
           "&apiKey=" + apiKey;
}

std::vector<std::string> NewsFetcher::fetch(int pageSize) {
    std::vector<std::string> headlines;
    std::string readBuffer;

    CURL* curl = curl_easy_init();
    if (!curl) return headlines;

    curl_easy_setopt(curl, CURLOPT_URL, constructUrl(pageSize).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
        try {
            std::cout << res << std::endl;
            auto json = nlohmann::json::parse(readBuffer);
            for (const auto& article : json["articles"]) {
                if (article.contains("title")) {
                    headlines.push_back(article["title"].get<std::string>());
                }
            }
        } catch (...) {
            std::cerr << "Failed to parse JSON.\n";
        }
    } else {
        std::cerr << "CURL error: " << curl_easy_strerror(res) << "\n";
    }

    curl_easy_cleanup(curl);
    return headlines;
}
