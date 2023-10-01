#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string>

const int MAX_BUFFER_SIZE = INT16_MAX;

// Function to fetch HTML content from a URL and port
std::string fetchHTML(const std::string& url, const std::string& port) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;  //ipv4
    hints.ai_socktype = SOCK_STREAM;    //tcp

    // Resolve the hostname
    int status = getaddrinfo(url.c_str(), port.c_str(), &hints, &res);
    if (status != 0) {
        std::cerr << "Error resolving hostname: " << gai_strerror(status) << std::endl;
        return "";
    }

    // Create a socket
    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        freeaddrinfo(res);
        return "";
    }

    // Connect to the server
    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sock);
        freeaddrinfo(res);
        return "";
    }

    // Send an HTTP GET request
    std::string request = "GET / HTTP/1.1\r\nHost: " + url + "\r\n\r\n";
    send(sock, request.c_str(), request.length(), 0);

    // Receive and store the response
    char buffer[MAX_BUFFER_SIZE];
    std::string htmlContent = "";
    int bytesRead;
    while ((bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';
        htmlContent += buffer;
    }

    // Close the socket
    close(sock);
    freeaddrinfo(res);

    return htmlContent;
}

int main() {
    std::string url = "www.iit.du.ac.bd"; 
    std::string port = "80";

    // Call the function to fetch HTML content
    std::string html = fetchHTML(url, port);

    // Print the HTML content
    std::cout << html << std::endl;

    return 0;
}