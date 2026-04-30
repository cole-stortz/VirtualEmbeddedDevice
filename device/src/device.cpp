#include "device.h"
#include "components/led.h"
#include <fstream>
#include <iostream>
#include "protocol.h"

bool Device::loadLayout(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[DEVICE] Failed to open layout file: " << filepath << "\n";
        return false;
    }

    json layout;
    try {
        file >> layout;
    } catch (const json::parse_error& e) {
        std::cerr << "[DEVICE] JSON parse error: " << e.what() << "\n";
        return false;
    }

    name = layout["device"]["name"];
    version = layout["device"]["version"];

    for (const auto& c : layout["components"]) {
        std::string type  = c["type"];
        std::string id    = c["id"];
        std::string label = c["label"];
        json state        = c["state"];

        if (type == "led") {
            auto led = std::make_shared<Led>(id, label, state);
            led->device = this;
            components.push_back(led);
        }
        // more types coming soon
    }

    return true;
}

void Device::printlayout() {
    std::cout << "Device Name: " << name << "\n";
    std::cout << "Version: " << version << "\n";
    std::cout << "Components:\n";
    for (const auto& c : components) {
        std::cout << "  - [" << c->type << "] " << c->id << " | " << c->label << "\n";
    }
}

json Device::getRawLayout() {
    std::ifstream file("../layout/layout.json");
    json layout;
    file >> layout;
    return layout;
}

std::shared_ptr<Component> Device::getComponent(const std::string& id) {
    for (const auto& c : components) {
        if (c->id == id) return c;
    }
    return nullptr;
}

std::shared_ptr<Led> Device::getLed(const std::string& id) {
    for (const auto& c : components) {
        if (c->id == id && c->type == "led") {
            return std::dynamic_pointer_cast<Led>(c);
        }
    }
    return nullptr;
}

void Device::delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void Device::sendStateUpdate(const std::string& component_id, const json& state) {
    json message;
    message["type"] = "STATE_UPDATE";
    message["payload"]["component_id"] = component_id;
    message["payload"]["state"] = state;
    sendMessage(sock, message.dump());
}

void Device::setLed(const std::string& id, bool on) {
    auto led = getLed(id);
    if (led) led->setState(on);
}
