// fetching data without using any library except openSSL

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
    size_t protocolPos = url.find("://");
    return (protocolPos != std::string::npos) ? url.substr(protocolPos + 3) : url;
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
    std::string host, path;
    std::string urlWithoutProtocol = removeProtocol(url);

    size_t pathPos = urlWithoutProtocol.find('/');
    if (pathPos != std::string::npos) {
        host = urlWithoutProtocol.substr(0, pathPos);
        path = urlWithoutProtocol.substr(pathPos);
    } else {
        host = urlWithoutProtocol;
        path = "/";
    }

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

//    auto start = std::chrono::high_resolution_clock::now();

    string html = getHTML(url);

/*    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Parsing time: " << duration.count() << " seconds" << std::endl;
*/

    //cout << "HTML data fetching done" << endl;

    std::string urlCopy(url);

//   start = std::chrono::high_resolution_clock::now();

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

/*    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end - start;
    std::cout << "Listing time: " << duration2.count() << " seconds" << std::endl;
*/

    return outLinks;
}



int main() {
    std::string url;
    std::cout << "Enter the URL: ";
    std::getline(std::cin, url);

    vector<string> outLinks = listOfOutgoingURLs(url);

    for(int i=0; i<outLinks.size(); i++){
        cout << outLinks[i] << endl;
    }

    ERR_free_strings();
    EVP_cleanup();

    return 0;
}