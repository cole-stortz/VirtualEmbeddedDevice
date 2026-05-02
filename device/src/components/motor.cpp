#include "components/motor.h"
#include "device.h"
#include <iostream>

void Motor::handleCommand(const std::string& action, const json& params) {
    if (action == "SET_SPEED") {
        if (params.contains("speed")){
            setSpeed(params["speed"]);
        }
    } else if (action == "SET_DIRECTION") {
        if (params.contains("direction")) {
            setDirection(params["direction"]);
        }
    } else {
        std::cout << "[Motor] " << id << " unknown action: " << action << "\n";
    }
}

void Motor::setSpeed(float speed) {
    state["speed"] = speed;
    std::cout << "Motor " << id << " speed set to " << speed << "\n";
    if (device) {
        device->sendStateUpdate(id, state);
    }
}

void Motor::setDirection(const std::string& direction) {
    state["direction"] = direction;
    std::cout << "Motor " << id << " direction set to " << direction << "\n";
    if (device) {
        device->sendStateUpdate(id, state);
    }
}