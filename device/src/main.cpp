#include <iostream>
#include "device.h"
#include "tcp_client.h"
#include "protocol.h"
#include "json.hpp"

using json = nlohmann::json;

int main() {
    // Load device layout
    Device device;
    if (!device.loadLayout("../layout/layout.json")) {
        std::cerr << "[Device] Failed to load layout. Exiting.\n";
        return 1;
    }
    device.printlayout();

    // Connect to server
    TcpClient client;
    if (!client.connect("127.0.0.1", 8080)) {
        std::cerr << "[Device] Failed to connect. Exiting.\n";
        return 1;
    }

    // build the HANDSHAKE message
    json handshake;
    handshake["type"] = "HANDSHAKE";
    handshake["payload"]["device_name"] = device.name;
    handshake["payload"]["version"] = device.version;
    handshake["payload"]["layout"] = device.getRawLayout();

    // send it
    sendMessage(client.sock, handshake.dump());
    std::cout << "[Device] Handshake sent\n";

    // wait for ACK
    std::string reply = receiveMessage(client.sock);
    std::cout << "[DEBUG] Raw reply: " << reply << "\n";  // Debugging line to see the raw reply
    json ack = json::parse(reply);
    if (ack["type"] == "HANDSHAKE_ACK" && ack["payload"]["status"] == "ok") {
        std::cout << "[Device] Handshake acknowledged\n";
    } else {
        std::cerr << "[Device] Unexpected response\n";
        client.disconnect();
        return 1;
    }

    // main loop
    std::cout << "[Device] Entering main loop...\n";
    while (true) {
        // Wait for messages from the server
        std::string raw = receiveMessage(client.sock);
        if (raw.empty()) {
            std::cout << "[Device] Connection closed by server.\n";
            break;
        }

        // Parse the message
        json message = json::parse(raw);
        std::string type = message["type"];
        std::cout << "[Device] Recieved: " << type << "\n";

        if (type == "COMMAND") {
            std::string component_id = message["payload"]["component_id"];
            std::string action = message["payload"]["action"];
            std::cout << "[Device] Command -> " << component_id << " : " << action << "\n";
        } else if (type == "QUIT") {
            std::cout << "[Device] Quit received. Disconnecting.\n";
            break;
        }
    }
    
    client.disconnect();
    return 0;
}