#include "components/button.h"
#include <iostream>

void Button::handleCommand(const std::string& action, const json& params) {
    if (action == "PRESS") {
        if (params.contains("pressed")) {
            state["pressed"] = params["pressed"];
            std::cout << "[BUTTON] " << id << " is " << (state["pressed"] ? "PRESSED" : "RELEASED") << "\n";
        }
    } else {
        std::cout << "[BUTTON] " << id << " unknown action: " << action << "\n";
    }
}