#pragma once
#include <winsock.h>
#include <string>
#include <cstdint>

void sendMessage(SOCKET socket, const std::string& message);
std::string receiveMessage(SOCKET socket);

