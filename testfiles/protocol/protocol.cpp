// protocol.cpp
#include "protocol.h"
#include <stdexcept>

// Sends a framed message: [4-byte length][json bytes]
void sendMessage(SOCKET sockfd, const std::string& json) {
    uint32_t length = htonl((u_long)json.size());  // htonl is in winsock2.h

    send(sockfd, (const char*)&length, sizeof(length), 0);
    send(sockfd, json.c_str(), (int)json.size(), 0);
}


// Reads a framed message: reads length header, then reads that many bytes
std::string recvMessage(SOCKET sockfd) {
    uint32_t length = 0; 
    int received = recv(sockfd, (char*)&length, sizeof(length), MSG_WAITALL); //
    if (received <= 0) throw std::runtime_error("Connection closed");

    length = ntohl(length);

    std::string buffer(length, '\0');
    received = recv(sockfd, &buffer[0], (int)length, MSG_WAITALL);
    if (received <= 0) throw std::runtime_error("Connection closed");

    return buffer;
}