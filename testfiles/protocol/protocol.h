// protocol.h
#pragma once
#include <string>
#include <cstdint>
#include <winsock2.h>  // replaces sys/socket.h + arpa/inet.h on Windows

#pragma comment(lib, "ws2_32.lib")  // auto-links the winsock library

void sendMessage(SOCKET sockfd, const std::string& json);
std::string recvMessage(SOCKET sockfd);