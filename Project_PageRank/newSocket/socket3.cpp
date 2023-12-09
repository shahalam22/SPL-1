#include <iostream>
#include <chrono>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <openssl/ssl.h>
#include <openssl/err.h>

using namespace std;

const int MAX_BUFFER_SIZE = INT16_MAX;

class PersistentConnection {
public:
    PersistentConnection() : sock(-1) {}

    ~PersistentConnection() {
        if (sock != -1) {
            close(sock);
        }
    }

    int getSocket() const {
        return sock;
    }

    bool connect(const string& host, const string& port) {
        if (sock != -1) {
            // Close existing connection
            close(sock);
        }

        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;  // IPv4
        hints.ai_socktype = SOCK_STREAM;    // TCP

        int status = getaddrinfo(host.c_str(), port.c_str(), &hints, &res);
        if (status != 0) {
            cerr << "Error resolving hostname: " << gai_strerror(status) << endl;
            return false;
        }

        sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sock == -1) {
            cerr << "Error creating socket" << endl;
            freeaddrinfo(res);
            return false;
        }

        if (::connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
            cerr << "Connection failed" << endl;
            close(sock);
            freeaddrinfo(res);
            return false;
        }

        freeaddrinfo(res);
        return true;
    }

private:
    int sock;
};

// Function to fetch HTML content from a URL using HTTP
string fetchHTTP(PersistentConnection& connection, const string& url, const string& port) {
    if (!connection.connect(url, port)) {
        return "";
    }

    string request = "GET / HTTP/1.1\r\nHost: " + url + "\r\n\r\n";
    send(connection.getSocket(), request.c_str(), request.length(), 0);

    char buffer[MAX_BUFFER_SIZE];
    string htmlContent = "";
    int bytesRead;
    while ((bytesRead = recv(connection.getSocket(), buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';
        htmlContent += buffer;
    }

    return htmlContent;
}

// Function to fetch HTML content from a URL using HTTPS
string fetchHTTPS(PersistentConnection& connection, const string& url, const string& port) {
    if (!connection.connect(url, port)) {
        return "";
    }

    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        cerr << "Error creating SSL context" << endl;
        return "";
    }

    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, connection.getSocket());

    if (SSL_connect(ssl) <= 0) {
        cerr << "SSL handshake failed" << endl;
        SSL_free(ssl);
        return "";
    }

    string request = "GET / HTTP/1.1\r\nHost: " + url + "\r\n\r\n";
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
    SSL_CTX_free(ctx);

    return htmlContent;
}

// Function to fetch HTML content from a URL (auto-detecting HTTP or HTTPS)
string fetchHTML(PersistentConnection& connection, const string& url) {
    size_t protocolPos = url.find("://");
    if (protocolPos == string::npos) {
        // If no protocol is specified, try HTTP by default
        return fetchHTTP(connection, url, "80");
    }

    string protocol = url.substr(0, protocolPos);
    if (protocol == "http") {
        // Use HTTP (port 80)
        return fetchHTTP(connection, url.substr(protocolPos + 3), "80");
    } else if (protocol == "https") {
        // Use HTTPS
        return fetchHTTPS(connection, url.substr(protocolPos + 3), "443");
    } else {
        cerr << "Unsupported protocol in URL: " << protocol << endl;
        return "";
    }
}

vector<string> listOfOutgoingURLs(PersistentConnection& connection, const string& url) {
    string html = fetchHTML(connection, url);

    std::string urlCopy(url);

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

    return outLinks;
}

int main() {
    string url = "https://www.prothomalo.com/"; // Change the URL as needed

    PersistentConnection connection;

    auto start = chrono::high_resolution_clock::now();
    vector<string> outLinks = listOfOutgoingURLs(connection, url);
    auto end = chrono::high_resolution_clock::now();

    for (const auto& link : outLinks) {
        cout << link << endl;
    }

    chrono::duration<double> duration = end - start;
    cout << "Total time: " << duration.count() << " seconds" << endl;

    return 0;
}
