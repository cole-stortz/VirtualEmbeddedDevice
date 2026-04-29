#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib for Winsock functions

class TcpClient {
    public:
        SOCKET sock;

        bool connect(const std::string& host, int port);
        void disconnect();
};