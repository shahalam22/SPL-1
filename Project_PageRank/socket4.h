#include <iostream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <vector>
#include <chrono>

using namespace std;


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


/*std::string removeProtocol(const std::string& url) {
    size_t protocolPos = url.find("://");
    return (protocolPos != std::string::npos) ? url.substr(protocolPos + 3) : url;
}*/

std::string extractHost(const std::string& url) {
    size_t pathPos = url.find('/');
    return (pathPos != std::string::npos) ? url.substr(0, pathPos) : url;
}

std::string extractPath(const std::string& url) {
    size_t pathPos = url.find('/');
    return (pathPos != std::string::npos) ? url.substr(pathPos) : "/";
}

int createSocket(const std::string& host) {
    struct addrinfo hints, *result;

    std::memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;  // Use IPv4
    hints.ai_socktype = SOCK_STREAM;

    // Resolve the IP address of the server
    if (getaddrinfo(host.c_str(), "443", &hints, &result) != 0) {
        std::cerr << "Failed to resolve the IP address\n";
        return -1;
    }

    struct sockaddr_in* serverAddress = reinterpret_cast<struct sockaddr_in*>(result->ai_addr);

    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket\n";
        freeaddrinfo(result);
        return -1;
    }

    // Connect to the server
    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(serverAddress), sizeof(*serverAddress)) == -1) {
        std::cerr << "Failed to connect to the server\n";
        close(clientSocket);
        freeaddrinfo(result);
        return -1;
    }

    freeaddrinfo(result);

    return clientSocket;
}

SSL_CTX* createSSLContext() {
    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        std::cerr << "Failed to create SSL context\n";
        ERR_print_errors_fp(stderr);
        return nullptr;
    }

    // Set cipher list
    if (SSL_CTX_set_cipher_list(ctx, "DEFAULT") != 1) {
        std::cerr << "Failed to set cipher list\n";
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return nullptr;
    }

    // Disable certificate verification (for testing purposes)
    SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, nullptr);

    return ctx;
}

SSL* createSSLConnection(int socket, SSL_CTX* ctx) {
    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        std::cerr << "Failed to create SSL connection\n";
        ERR_print_errors_fp(stderr);
        return nullptr;
    }
    if (SSL_set_fd(ssl, socket) == 0) {
        std::cerr << "Failed to set SSL file descriptor\n";
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        return nullptr;
    }
    if (SSL_connect(ssl) <= 0) {
        std::cerr << "Failed to establish SSL connection\n";
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        return nullptr;
    }
    return ssl;
}

std::string getHTML(const std::string& url) {
    std::string host = extractHost(url);
    std::string path = extractPath(url);

    int clientSocket = createSocket(host);
    if (clientSocket == -1) {
        return "";
    }

    SSL_CTX* sslContext = createSSLContext();
    if (!sslContext) {
        close(clientSocket);
        return "";
    }

    SSL* ssl = createSSLConnection(clientSocket, sslContext);
    if (!ssl) {
        SSL_CTX_free(sslContext);
        close(clientSocket);
        return "";
    }

    // Send an HTTP GET request
    std::ostringstream requestStream;
    requestStream << "GET " << path << " HTTP/1.1\r\nHost: " << host << "\r\nConnection: close\r\n\r\n";
    std::string httpRequest = requestStream.str();

    if (SSL_write(ssl, httpRequest.c_str(), httpRequest.size()) <= 0) {
        std::cerr << "Failed to send HTTP request\n";
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        SSL_CTX_free(sslContext);
        close(clientSocket);
        return "";
    }

    // Receive and extract the HTML content
    std::ostringstream htmlStream;
    char buffer[4096];
    int bytesRead;

    while ((bytesRead = SSL_read(ssl, buffer, sizeof(buffer))) > 0) {
        htmlStream.write(buffer, bytesRead);
    }

    SSL_free(ssl);
    SSL_CTX_free(sslContext);
    close(clientSocket);

    return htmlStream.str();
}

vector<string> listOfOutgoingURLs(const string& url) {

    std::string newUrl(removeProtocol(url));

    string html = getHTML(newUrl);

    std::string urlCopy(url);


    vector<string> outLinks{};
    while (html.find("<a") != string::npos) {
        if (html.find("href=\"") != string::npos) {
            size_t start = html.find("href=\"");
            size_t end = html.find("\"", start + 6);
            if (end != string::npos) {
                string url = html.substr(start + 6, end - start - 6);

                // Handle relative URLs
                if (url.find("http") != 0) {
                    url = urlCopy + url;
                }

                outLinks.push_back(url);
                html = html.substr(end + 1);
            } else {
                break;  // Break if closing quote not found
            }
        } else {
            break;  // Break if "href" not found
        }
    }



/*
    vector<string> outLinks{};
    while (html.find("<a") != string::npos) {
        if (html.find("href=\"") != string::npos) {
            int start = html.find("href=\"");
            int end = html.find("\"", start + 6);
            string url = html.substr(start + 6, end - start - 6);
            if (url.find(urlCopy) != string::npos) {
                outLinks.push_back(url);
            }
            html = html.substr(end + 1);
        }
    }
*/



    return outLinks;
}

/*
int main() {
    std::string url;
    std::cout << "Enter the URL: ";
    std::getline(std::cin, url);

    url = removeProtocol(url);

    vector<string> outLinks = listOfOutgoingURLs(url);

    for (int i = 0; i < outLinks.size(); i++) {
        cout << outLinks[i] << endl;
    }

    ERR_free_strings();
    EVP_cleanup();

    return 0;
}
*/