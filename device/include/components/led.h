#pragma once
#include "component.h"

class Led : public Component {
    public:
        Led(const std::string& id, const std::string& label, const json& state)
            : Component(id, "led", label, state) {}

        void handleCommand(const std::string& action, const json& params) override;
};