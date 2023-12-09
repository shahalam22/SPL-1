#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <thread>
#include <mutex>
#include <unordered_map>
using namespace std;

const int MAX_BUFFER_SIZE = INT16_MAX;
std::mutex mtx; // Mutex for thread safety

// Cache to store fetched HTML content
std::unordered_map<string, string> cache;

// Function to fetch HTML content from a URL using HTTP
string fetchHTTP(const string& url, const string& port) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;  // IPv4
    hints.ai_socktype = SOCK_STREAM;    // TCP

    int status = getaddrinfo(url.c_str(), port.c_str(), &hints, &res);
    if (status != 0) {
        cerr << "Error resolving hostname: " << gai_strerror(status) << endl;
        return "";
    }

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == -1) {
        cerr << "Error creating socket" << endl;
        freeaddrinfo(res);
        return "";
    }

    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
        cerr << "Connection failed" << endl;
        close(sock);
        freeaddrinfo(res);
        return "";
    }

    string request = "GET / HTTP/1.1\r\nHost: " + url + "\r\n\r\n";
    send(sock, request.c_str(), request.length(), 0);

    char buffer[MAX_BUFFER_SIZE];
    string htmlContent = "";
    int bytesRead;
    while ((bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';
        htmlContent += buffer;
    }

    close(sock);
    freeaddrinfo(res);

    return htmlContent;
}

// Function to fetch HTML content from a URL using HTTPS
string fetchHTTPS(const string& url, const string& port) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        cerr << "Error creating SSL context" << endl;
        return "";
    }

    // // Extract the hostname from the URL
    // size_t protocolPos = url.find("://");
    // if (protocolPos == string::npos) {
    //     cerr << "Invalid URL format: " << url << endl;
    //     return "";
    // }

    string host = url;
    size_t pathPos = host.find("/");
    if (pathPos != string::npos) {
        host = host.substr(0, pathPos);
    }

    // Resolve the hostname
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0) {
        cerr << "Error resolving hostname" << endl;
        return "";
    }

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == -1) {
        cerr << "Error creating socket" << endl;
        freeaddrinfo(res);
        return "";
    }

    if (connect(sock, res->ai_addr, res->ai_addrlen) == -1) {
        cerr << "Error connecting to server" << endl;
        close(sock);
        freeaddrinfo(res);
        return "";
    }

    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);

    if (SSL_connect(ssl) <= 0) {
        cerr << "SSL handshake failed" << endl;
        SSL_free(ssl);
        close(sock);
        freeaddrinfo(res);
        SSL_CTX_free(ctx);
        return "";
    }

    string request = "GET / HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
    SSL_write(ssl, request.c_str(), request.length());

    char buffer[MAX_BUFFER_SIZE];
    string htmlContent = "";
    int bytesRead;
    while ((bytesRead = SSL_read(ssl, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';
        htmlContent += buffer;
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sock);
    freeaddrinfo(res);
    SSL_CTX_free(ctx);

    return htmlContent;
}

string fetchHTML(const string& url) {
    // Check if the content is cached
    std::lock_guard<std::mutex> lock(mtx);
    if (cache.find(url) != cache.end()) {
        return cache[url];
    }

    // If not cached, fetch the content
    string htmlContent;
    size_t protocolPos = url.find("://");
    if (protocolPos == string::npos) {
        // If no protocol is specified, try HTTP by default
        htmlContent = fetchHTTP(url, "80");
    } else {
        string protocol = url.substr(0, protocolPos);
        if (protocol == "http") {
            // Use HTTP (port 80)
            htmlContent = fetchHTTP(url.substr(protocolPos + 3), "80");
        } else if (protocol == "https") {
            // Use HTTPS
            htmlContent = fetchHTTPS(url.substr(protocolPos + 3), "443");
        } else {
            cerr << "Unsupported protocol in URL: " << protocol << endl;
            return "";
        }
    }

    // Cache the fetched content
    cache[url] = htmlContent;
    return htmlContent;
}

vector<string> listOfOutgoingURLs(const string& url) {
    string html = fetchHTML(url);
    vector<string> outLinks{};
    while (html.find("<a") != string::npos) {
        if (html.find("href=\"") != string::npos) {
            int start = html.find("href=\"");
            int end = html.find("\"", start + 6);
            string url = html.substr(start + 6, end - start - 6);
            if (url.find("http") != string::npos) {
                outLinks.push_back(url);
            }
            html = html.substr(end + 1);
        }
    }
    return outLinks;
}

// Function to fetch outgoing URLs in parallel
void processURL(const string& url) {
    vector<string> outLinks = listOfOutgoingURLs(url);

    // Print links in a thread-safe manner
    std::lock_guard<std::mutex> lock(mtx);
    for (const auto& link : outLinks) {
        cout << link << endl;
    }
}

int main() {
    vector<string> urls = {
        "https://www.prothomalo.com/",
        // Add more URLs as needed
    };

    vector<thread> threads;
    for (const auto& url : urls) {
        threads.emplace_back(processURL, url);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
