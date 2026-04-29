// main.cpp
#include <iostream>
#include "device.h"
#include "tcp_client.h"

int main() {
    Device device;

    if (!device.loadLayout("../layout/layout.json")) {
        std::cerr << "[Device] Failed to load layout. Exiting.\n";
        return 1;
    }

    device.printlayout();

    TcpClient client;
    if (!client.connect("127.0.0.1", 8080)) {
        std::cerr << "[Device] Failed to connect to server. Exiting.\n";
        return 1;
    }

    client.disconnect();
    return 0;
}