#pragma once
#include "component.h"

class Device;  // forward declaration

class Sensor : public Component {
    public:
        Device* device;  // pointer back to device for state updates

        Sensor(const std::string& id, const std::string& label, const json& state)
            : Component(id, "sensor", label, state), device(nullptr) {}
        
        void handleCommand(const std::string& action, const json& params) override;

        void setValue(float value);
        void setColor(int r, int g, int b);
};