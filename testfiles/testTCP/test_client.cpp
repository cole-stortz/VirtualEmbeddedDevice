#include <iostream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdint>

#pragma comment(lib, "ws2_32.lib")


const char* HOST = "127.0.0.1"; // Localhost
const int PORT = 8080; // Port number

void send_message(SOCKET sock, const std::string& message) {
    uint32_t len = htonl((uint32_t)message.size()); // Convert length to 4 bytes
    send(sock, (const char*)&len, sizeof(len), 0); // Send length header
    send(sock, message.c_str(), (int)message.size(), 0); // Send message body
}

std::string recv_message(SOCKET sock) {
    // read exactly 4 bytes for the length header
    uint32_t len = 0;
    int total = 0;
    while (total < 4) {
        int bytes = recv(sock, (char*)&len + total, 4 - total, 0);  // 0 instead of MSG_WAITALL
        if (bytes <= 0) return "";
        total += bytes;
    }
    len = ntohl(len);

    // read exactly that many bytes
    std::string buffer(len, '\0');
    total = 0;
    while (total < (int)len) {
        int bytes = recv(sock, &buffer[total], len - total, 0);  // 0 instead of MSG_WAITALL
        if (bytes <= 0) return "";
        total += bytes;
    }
    return buffer;
}


// Function to handle the chat loop
void chat_loop(SOCKET sock) {
    std::string message;

    while (true) {
        std::cout << "[You (client)]: ";
        std::getline(std::cin, message);
        std::cout << "[DEBUG] You typed: '" << message << "' length=" << message.size() << "\n";

        send_message(sock, message);

        if (message == "quit" || message == "exit") {
            std::cout << "[Client] Closing connection.\n";
            return;
        }

        std::string reply = recv_message(sock);
        if (reply.empty()) {
            std::cout << "[Client] Server disconnected.\n";
            return;
        }

        std::cout << "[Server]: " << reply << "\n";

        if (reply == "quit" || reply == "exit") {
            std::cout << "[Client] Server ended the chat.\n";
            return;
        }
    }
}

SOCKET create_and_connect() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(HOST);

    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return INVALID_SOCKET;
    }

    return sock;
}

void cleanup(SOCKET sock) {
    closesocket(sock);
    WSACleanup();
}

int main() {
    SOCKET sock = create_and_connect();
    if (sock == INVALID_SOCKET) return 1;

    std::cout << "[Client] Connected to " << HOST << ":" << PORT << "\n\n";
    chat_loop(sock);
    cleanup(sock);
    return 0;
}