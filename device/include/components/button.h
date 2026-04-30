#pragma once
#include "component.h"

class Button : public Component {
    public:
        Button(const std::string& id, const std::string& label, const json& state)
            : Component(id, "button", label, state) {}

        void handleCommand(const std::string& action, const json& params) override;
};