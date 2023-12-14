// Socket using CURL library
// fetching html code using LIBCURL library

#include <iostream>
#include <curl/curl.h>

// Callback function to write fetched data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main() {
    // Initialize cURL
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the URL to fetch
        const char* url = "https://www.prothomalo.com/bangladesh/mys4oko96c";
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Set the callback function to write fetched data
        std::string fetchedData;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fetchedData);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Clean up
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        // Print the fetched HTML code
        std::cout << "Fetched HTML code:\n" << fetchedData << std::endl;
    }

    return 0;
}
