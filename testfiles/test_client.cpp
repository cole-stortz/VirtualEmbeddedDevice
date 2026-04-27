#include <iostream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

const char* HOST = "127.0.0.1";
const int PORT = 8080;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(HOST);

    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    std::cout << "[Client] Connected to " << HOST << ":" << PORT << "\n\n";

    char buffer[1024];
    std::string message;

    while (true) {
        std::cout << "[You (client)]: ";
        std::getline(std::cin, message);

        send(sock, message.c_str(), message.size(), 0);

        if (message == "quit" || message == "exit") {
            std::cout << "[Client] Closing connection.\n";
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) {
            std::cout << "[Client] Server disconnected.\n";
            break;
        }

        std::string reply(buffer, bytes);
        std::cout << "[Server]: " << reply << "\n";

        if (reply == "quit" || reply == "exit") {
            std::cout << "[Client] Server ended the chat.\n";
            break;
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}