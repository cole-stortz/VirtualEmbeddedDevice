#pragma once
#include <string>
#include "../json.hpp"

using json = nlohmann::json;

class Component {
    public:
        std::string id;
        std::string type;
        std::string label;
        json state;

        Component(const std::string& id, const std::string& type, const std::string& label, const json& state)
            : id(id), type(type), label(label), state(state) {}

        virtual void handleCommand(const std::string& action, const json& params) = 0;
        virtual json getState() const {return state;}

        virtual ~Component() {}
        
};