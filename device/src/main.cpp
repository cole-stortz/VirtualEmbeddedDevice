#include <iostream>
#include "device.h"
#include "tcp_client.h"
#include "protocol.h"

int main() {
    Device device;
    if (!device.loadLayout("../layout/layout.json")) {
        std::cerr << "[Device] Failed to load layout. Exiting.\n";
        return 1;
    }
    device.printlayout();

    TcpClient client;
    if (!client.connect("127.0.0.1", 8080)) {
        std::cerr << "[Device] Failed to connect. Exiting.\n";
        return 1;
    }

    // test sending a framed message
    sendMessage(client.sock, "hello from device");

    // test receiving a framed reply
    std::string reply = receiveMessage(client.sock);
    std::cout << "[Device] Server replied: " << reply << "\n";

    client.disconnect();
    return 0;
}