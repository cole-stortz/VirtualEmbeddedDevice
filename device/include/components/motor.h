#pragma once
#include "component.h"

class Device;  // forward declaration

class Motor : public Component {
    public:
        Device* device;  // pointer back to device for state updates

        Motor(const std::string& id, const std::string& label, const json& state)
            : Component(id, "motor", label, state), device(nullptr) {}
        
        void handleCommand(const std::string& action, const json& params) override;

        void setSpeed(float speed);
        void setDirection(const std::string& direction);
};