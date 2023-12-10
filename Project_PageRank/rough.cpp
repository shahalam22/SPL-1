#include <iostream>
#include <string>

std::string removeProtocol(const std::string& url) {
    std::string httpPrefix = "http://";
    std::string httpsPrefix = "https://";

    // Check if the URL starts with "http://"
    if (url.compare(0, httpPrefix.length(), httpPrefix) == 0) {
        return url.substr(httpPrefix.length());
    }

    // Check if the URL starts with "https://"
    if (url.compare(0, httpsPrefix.length(), httpsPrefix) == 0) {
        return url.substr(httpsPrefix.length());
    }

    // If no prefix is found, return the original URL
    return url;
}

int main() {
    std::string url;
    std::cout << "Enter the URL: ";
    std::getline(std::cin, url);

    std::string cleanedUrl = removeProtocol(url);
    std::cout << "Cleaned URL: " << cleanedUrl << std::endl;

    return 0;
}
