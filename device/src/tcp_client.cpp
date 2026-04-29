#include "tcp_client.h"
#include <iostream>

// Connect to the server at the specified host and port
bool TcpClient::connect(const std::string& host, int port) {
    // Initialize Winsock
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Set up the server address structure
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(host.c_str());

    // Connect to the server
    if (::connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "[TCP] Connection failed\n" << std::endl;
        return false;
    }
    
    std::cout << "[TCP] Connected to " << host << ":" << port << "\n";
    return true;
}

// Disconnect from the server and clean up Winsock
void TcpClient::disconnect() {
    closesocket(sock);
    WSACleanup();
    std::cout << "[TCP] Disconnected\n";
}