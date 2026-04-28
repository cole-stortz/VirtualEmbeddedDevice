#include <iostream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

const char* HOST = "127.0.0.1"; // Localhost
const int PORT = 8080; // Port number


// Function to handle the chat loop
void chat_loop(SOCKET sock) {
    char buffer[1024]; // Buffer for receiving messages
    std::string message; // Variable for user input

    while (true) {
        std::cout << "[You (client)]: ";
        std::getline(std::cin, message);

        send(sock, message.c_str(), message.size(), 0);

        if (message == "quit" || message == "exit") {
            std::cout << "[Client] Closing connection.\n";
            return;
        }

        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) {
            std::cout << "[Client] Server disconnected.\n";
            return;
        }

        std::string reply(buffer, bytes);
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