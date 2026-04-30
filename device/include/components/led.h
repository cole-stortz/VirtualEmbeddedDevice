#pragma once
#include "component.h"

class Device;  // forward declaration

class Led : public Component {
public:
    Device* device;  // pointer back to device for state updates

    Led(const std::string& id, const std::string& label, const json& state)
        : Component(id, "led", label, state), device(nullptr) {}

    void setState(bool on);
    void handleCommand(const std::string& action, const json& params) override;
};