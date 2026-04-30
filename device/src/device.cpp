#include "device.h"
#include "components/led.h"
#include <fstream>
#include <iostream>

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
            components.push_back(std::make_shared<Led>(id, label, state));
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