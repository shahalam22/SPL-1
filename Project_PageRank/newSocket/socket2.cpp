#include <iostream>
#include <string>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

std::string fetchHTML(const std::string& url) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    std::string htmlContent;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlContent);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "cURL failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return htmlContent;
}

int main() {
    std::string url = "http://www.prothomalo.com"; // Replace with the desired URL

    std::string htmlContent = fetchHTML(url);

    if (!htmlContent.empty()) {
        std::cout << "HTML Content:\n" << htmlContent << std::endl;
    } else {
        std::cerr << "Failed to fetch HTML content." << std::endl;
    }

    return 0;
}
