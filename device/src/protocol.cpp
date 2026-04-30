#include "protocol.h"
#include <iostream>

void sendMessage(SOCKET socket, const std::string& message) {
    uint32_t length = htonl((uint32_t)message.size()); // Convert length to network byte order
    send(socket, (const char*)&length, sizeof(length), 0); // Send the length first
    send(socket, message.c_str(), message.size(), 0); // Then send the actual message
}

std::string receiveMessage(SOCKET socket) {
    uint32_t length = 0;
    int total = 0;

    // Receive the length of the message (4 bytes)
    while (total < 4) {
        int bytes = recv(socket, (char*)&length + total, 4 - total, 0); // Receive the length first
        if (bytes <= 0) return ""; // Connection closed or error
        total += bytes;
    }
    length = ntohl(length); // Convert length from network byte order to host byte order

    std::string buffer(length, '\0');
    total = 0;
    while (total < (int)length) {
        // Receive the actual message
        int bytes = recv(socket, &buffer[total], length - total, 0); 
        if (bytes <= 0) return ""; // Connection closed or error
        total += bytes;
    }
    return buffer;
}