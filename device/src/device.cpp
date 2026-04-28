#include "device.h"
#include <fstream>
#include <iostream>

bool Device::loadLayout(const std::string& filepath) {
    // open the file
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[DEVICE] Failed to open layout file: " << filepath << "\n";
        return false;
    }

    // parse the JSON
    json layout;
    try {
        file >> layout;
    } catch (const json::parse_error& e) {
        std::cerr << "[DEVICE] JSON parse error: " << e.what() << "\n";
        return false;
    }

    // load device info
    name = layout["device"]["name"];
    version = layout["device"]["version"];

    // load components
    for (const auto& c : layout["components"]) {
        Component comp;
        comp.id = c["id"];
        comp.type = c["type"];
        comp.label = c["label"];
        comp.state = c["state"];
        
        // store any extra fields (sensor_type, unit etc)
        if (c.contains("sensor_type"))comp.extra["sensor_type"] = c["sensor_type"];
        if (c.contains("unit"))comp.extra["unit"] = c["unit"];

        components.push_back(comp);
    }
    return true;
}

void Device::printlayout() {
    std::cout << "Device Name: " << name << "\n";
    std::cout << "Version: " << version << "\n";
    std::cout << "Components:\n";
    for (const auto& comp : components) {
        std::cout << "  - [" << comp.type << "] " << comp.id << " | " << comp.label << "\n";
    }
}