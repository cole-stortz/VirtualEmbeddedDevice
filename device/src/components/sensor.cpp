#include "components/sensor.h"
#include "device.h"
#include <iostream>

void Sensor::handleCommand(const std::string& action, const json& params) {
    if (action == "SET_VALUE") {
        if (params.contains("value")){
            setValue(params["value"]);
        }
    } else if (action == "SET_COLOR") {
        if (params.contains("r") && params.contains("g") && params.contains("b")) {
            setColor(params["r"], params["g"], params["b"]);
        }
    } else {
        std::cout << "[Sensor] " << id << " unknown action: " << action << "\n";
    }
}

void Sensor::setValue(float value) {
    state["value"] = value;
    std::cout << "Sensor " << id << " value set to " << value << "\n";
    if (device) {
        device->sendStateUpdate(id, state);
    }
}

void Sensor::setColor(int r, int g, int b) {
    state["r"] = r;
    state["g"] = g;
    state["b"] = b;
    std::cout << "Sensor " << id << " color set to (" << r << ", " << g << ", " << b << ")\n";
    if (device) {
        device->sendStateUpdate(id, state);
    }
}