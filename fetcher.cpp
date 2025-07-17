// fetcher.cpp
#include "fetcher.hpp"
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>

NewsFetcher::NewsFetcher(const std::string& apiKey, const std::string& country, const std::string& category)
    : apiKey(apiKey), country(country), category(category) {}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<std::string> NewsFetcher::fetch(int pageSize) {
    std::vector<std::string> headlines;
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    std::string url = "https://newsapi.org/v2/top-headlines?country=" + country + "&category=" + category + "&pageSize=" + std::to_string(pageSize) + "&apiKey=" + apiKey;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Parse JSON
        auto jsonResponse = nlohmann::json::parse(readBuffer);
        for (const auto& article : jsonResponse["articles"]) {
            headlines.push_back(article["title"].get<std::string>());
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return headlines;
}
