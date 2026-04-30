#include "components/led.h"
#include "device.h"
#include <iostream>

void Led::setState(bool on) {
    state["on"] = on;
    std::cout << "LED " << id << " turned " << (on ? "ON" : "OFF") << "\n";
    if (device) {
        device->sendStateUpdate(id, state);
    }
}

void Led::handleCommand(const std::string& action, const json& params) {
    if (action == "SET_STATE") {
        if (params.contains("on")){
            setState(params["on"]);
        }
    } else {
        std::cout << "[LED] " << id << " unknown action: " << action << "\n";
    }
}