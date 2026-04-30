#include "components/led.h"
#include <iostream>

void Led::handleCommand(const std::string& action, const json& params) {
    if (action == "SET_STATE") {
        if (params.contains("on")){
            state["on"] = params["on"];
            std::cout << "[LED] " << id << " turned " << (state["on"] ? "ON" : "OFF") << "\n";
        }
    } else {
        std::cout << "[LED] " << id << " unknown action: " << action << "\n";
    }
}